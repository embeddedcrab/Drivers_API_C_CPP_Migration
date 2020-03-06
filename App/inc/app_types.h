/*
 * app_types.h
 *
 *  Created on: 30-Jun-2019
 *      Author: hp
 */

#ifndef APP_INC_APP_TYPES_H_
#define APP_INC_APP_TYPES_H_


/*
 * @brief	Enum for Status of API
 * */
typedef enum eAPP_Status_
{
	APP_STATUS_SUCCESS = 0,
	APP_STATUS_FAILED,
	APP_STATUS_BUSY,
	APP_STATUS_INVALID_ARGUMENT,
	APP_STATUS_OUT_OF_BOUND,
	APP_STATUS_ALREADY_INITIALIZED,
	APP_STATUS_NOT_INITIALIZED,
	APP_STATUS_NOT_AVAILABLE
} eAPP_Status;



/* Parameters for task creation */
typedef struct TaskCreationParams_
{
	char * p_name;
	configSTACK_DEPTH_TYPE stackDepth;
	UBaseType_t priority;
}TaskCreationParams;


#ifdef __cplusplus
extern "C"{
#endif





#ifdef __cplusplus
}
#endif


#endif /* APP_INC_APP_TYPES_H_ */
