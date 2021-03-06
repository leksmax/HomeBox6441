#include "ol_if_athvar.h"
#include "htc_packet.h"
#include "ol_helper.h"

struct cookie *cookie_list;
int cookie_count = 0;
#define MAX_COOKIE_NUM  1024
static struct cookie s_cookie_mem[MAX_COOKIE_NUM];
adf_os_spinlock_t cookie_lock;

void
ol_cookie_init(void *ar)
{
    A_UINT32    i;
    cookie_list = NULL;
    cookie_count = 0;
    OS_MEMZERO(s_cookie_mem, sizeof(s_cookie_mem));
	adf_os_spinlock_init(&cookie_lock);
    for (i = 0; i < MAX_COOKIE_NUM; i++) {
        ol_free_cookie(ar, &s_cookie_mem[i]);
    }
}

/* cleanup cookie queue */
void
ol_cookie_cleanup(void *ar)
{
    /* It is gone .... */
	adf_os_spin_lock_bh(&cookie_lock);
    cookie_list = NULL;
    cookie_count = 0;
	adf_os_spin_unlock_bh(&cookie_lock);
}

void
ol_free_cookie(void *ar, struct cookie *cookie)
{	
	adf_os_spin_lock_bh(&cookie_lock);
    cookie->arc_list_next = cookie_list;
    cookie_list = cookie;
    cookie_count++;
	adf_os_spin_unlock_bh(&cookie_lock);
}

/* cleanup cookie queue */
struct cookie *
ol_alloc_cookie(void  *ar)

{
    struct cookie   *cookie;

	adf_os_spin_lock_bh(&cookie_lock);
    cookie = cookie_list;
    if(cookie != NULL)
    {
        cookie_list = cookie->arc_list_next;
        cookie_count--;
    }
	adf_os_spin_unlock_bh(&cookie_lock);
    return cookie;
}

