#ifndef _Local_H_
#define _Local_H_

#include <CONNAC.h>

///// DEBUGGING MACROS ///////////////////////////////////////////////////////



///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
int local_conn_get_one_perflow(connState* conn_state);
static void *conn_sender(void *arg);
int local_conn_get_perflow();

int local_conn_put_perflow(ConnState* recv_state);
int local_action_get_perflow();
int local_action_put_perflow(ActionState* recv_state);

#endif
