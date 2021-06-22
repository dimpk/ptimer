/*/ 
 *    ptimer: notifications.c
 *
 *    Created by dimpk
/*/

#include <libnotify/notify.h>
#include "notifications.h"

void notification_show(const char *message) 
{
    notify_init("ptimer");
    NotifyNotification *n = notify_notification_new ("ptimer", message, 0);
    notify_notification_set_timeout(n, NOTIFY_EXPIRES_DEFAULT);
    notify_notification_show(n, 0);
}
