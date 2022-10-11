
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "model_1.h"
#include "model_1_data.h"
#include "model_2.h"
#include "model_2_data.h"

/* USER CODE BEGIN includes */
/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_MODEL_1_INPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_in_1[AI_MODEL_1_IN_1_SIZE_BYTES];
AI_ALIGNED(4) ai_i8 data_in_2[AI_MODEL_1_IN_1_SIZE_BYTES];
ai_i8* data_ins[AI_MNETWORK_NUMBER] = {
data_in_1, data_in_2
};
#else
ai_i8* data_ins[AI_MODEL_1_IN_NUM] = {
NULL
};
#endif

#if !defined(AI_MODEL_1_OUTPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_out_1[AI_MODEL_1_OUT_1_SIZE_BYTES];
AI_ALIGNED(4) ai_i8 data_out_2[AI_MODEL_1_OUT_1_SIZE_BYTES];
ai_i8* data_outs[AI_MNETWORK_NUMBER] = {
data_out_1, data_out_2
};
#else
ai_i8* data_outs[AI_MODEL_1_OUT_NUM] = {
NULL
};
#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
static uint8_t pool0[AI_MODEL_1_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};
ai_handle data_activations1[] = {pool0};

/* AI objects ----------------------------------------------------------------*/
typedef enum
{
  AI_MODEL_1 = 0,
  AI_MODEL_2 = 1,
  AI_MODEL_TOTAL_NUM,
} AI_MODEL_e;

static ai_handle model_1 = AI_HANDLE_NULL;
static ai_handle model_2 = AI_HANDLE_NULL;

static ai_buffer* ai_input[AI_MNETWORK_NUMBER] = {NULL,NULL};
static ai_buffer* ai_output[AI_MNETWORK_NUMBER] = {NULL,NULL};

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model 1 */
  err = ai_model_1_create_and_init(&model_1, act_addr, NULL);
  if (err.type != AI_ERROR_NONE)
  {
    ai_log_err(err, "ai_model_1_create_and_init");
    return -1;
  }

  ai_input[AI_MODEL_1] = ai_model_1_inputs_get(model_1, NULL);
  ai_output[AI_MODEL_1] = ai_model_1_outputs_get(model_1, NULL);
  ai_input[AI_MODEL_1]->data = data_ins[AI_MODEL_1];
  ai_output[AI_MODEL_1]->data = data_outs[AI_MODEL_1];

  /* Create and initialize an instance of the model 2 */
  err = ai_model_2_create_and_init(&model_2, act_addr, NULL);
  if (err.type != AI_ERROR_NONE)
  {
    ai_log_err(err, "ai_model_1_create_and_init");
    return -1;
  }

  ai_input[AI_MODEL_2] = ai_model_2_inputs_get(model_2, NULL);
  ai_output[AI_MODEL_2] = ai_model_2_outputs_get(model_2, NULL);
  ai_input[AI_MODEL_2]->data = data_ins[AI_MODEL_2];
  ai_output[AI_MODEL_2]->data = data_outs[AI_MODEL_2];

  return 0;
}

#if 0 // Use the training dataset as input for testing 13 attribute and 1 result.
0.00632  18.00   2.310  0  0.5380  6.5750  65.20  4.0900   1  296.0  15.30 396.90   4.98  24.00
0.02731   0.00   7.070  0  0.4690  6.4210  78.90  4.9671   2  242.0  17.80 396.90   9.14  21.60
0.02729   0.00   7.070  0  0.4690  7.1850  61.10  4.9671   2  242.0  17.80 392.83   4.03  34.70
0.03237   0.00   2.180  0  0.4580  6.9980  45.80  6.0622   3  222.0  18.70 394.63   2.94  33.40
0.06905   0.00   2.180  0  0.4580  7.1470  54.20  6.0622   3  222.0  18.70 396.90   5.33  36.20
#endif

const float input_data_1[AI_MODEL_1_IN_1_SIZE] = {0.00632,  18.00,   2.310,  0,  0.5380,  6.5750,  65.20,  4.0900,   1,  296.0,  15.30, 396.90,   4.98};
const float input_data_2[AI_MODEL_2_IN_1_SIZE] = {0.02731,   0.00,   7.070,  0,  0.4690,  6.4210,  78.90,  4.9671,   2,  242.0,  17.80, 396.90,   9.14};

float result_1 = 0, result_2 = 0;

static int ai_run(void)
{
  ai_i32 batch;

  /* AI Inference of Model 1 */
  for(int i = 0; i < AI_MODEL_1_IN_1_SIZE_BYTES; i++)
  {
    data_ins[AI_MODEL_1][i] = *((ai_i8*)input_data_1+i);
  }

  batch = ai_model_1_run(model_1, ai_input[AI_MODEL_1], ai_output[AI_MODEL_1]);

  if (batch != 1) {
    ai_log_err(ai_model_1_get_error(model_1),
        "ai_model_1_run");
    return -1;
  }else{
    result_1 = *((ai_float*)data_outs[AI_MODEL_1]);
  }

  /* AI Inference of Model 2 */
  for(int i = 0; i < AI_MODEL_2_IN_1_SIZE_BYTES; i++)
  {
    data_ins[AI_MODEL_2][i] = *((ai_i8*)input_data_2+i);
  }

  batch = ai_model_2_run(model_2, ai_input[AI_MODEL_2], ai_output[AI_MODEL_2]);

  if (batch != 1) {
    ai_log_err(ai_model_1_get_error(model_2),
        "ai_model_2_runs");
    return -1;
  }else{
    result_2 = *((ai_float*)data_outs[AI_MODEL_2]);
  }

  return 0;
}

/* USER CODE BEGIN 2 */
int acquire_and_process_data(ai_i8* data[])
{
  /* fill the inputs of the c-model
  for (int idx=0; idx < AI_MODEL_1_IN_NUM; idx++ )
  {
      data[idx] = ....
  }

  */
  return 0;
}

int post_process(ai_i8* data[])
{
  /* process the predictions
  for (int idx=0; idx < AI_MODEL_1_OUT_NUM; idx++ )
  {
      data[idx] = ....
  }

  */
  return 0;
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
  printf("\r\nTEMPLATE - initialization\r\n");

  ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
  int res = -1;

  printf("TEMPLATE - run - main loop\r\n");

  if (model_1) {

    do {
      /* 1 - acquire and pre-process input data */
      res = acquire_and_process_data(data_ins);
      /* 2 - process the data - call inference engine */
      if (res == 0)
        res = ai_run();
      /* 3- post-process the predictions */
      if (res == 0)
        res = post_process(data_outs);
    } while (res==0);
  }

  if (res) {
    ai_error err = {AI_ERROR_INVALID_STATE, AI_ERROR_CODE_NETWORK};
    ai_log_err(err, "Process has FAILED");
  }
    /* USER CODE END 6 */
}
/* Multiple network support --------------------------------------------------*/

#include <string.h>
#include "ai_datatypes_defines.h"

static const ai_network_entry_t networks[AI_MNETWORK_NUMBER] = {
    {
        .name = (const char *)AI_MODEL_1_MODEL_NAME,
        .config = AI_MODEL_1_DATA_CONFIG,
        .ai_get_report = ai_model_1_get_report,
        .ai_create = ai_model_1_create,
        .ai_destroy = ai_model_1_destroy,
        .ai_get_error = ai_model_1_get_error,
        .ai_init = ai_model_1_init,
        .ai_run = ai_model_1_run,
        .ai_forward = ai_model_1_forward,
        .ai_data_params_get = ai_model_1_data_params_get,
        .activations = data_activations0
    },
    {
        .name = (const char *)AI_MODEL_2_MODEL_NAME,
        .config = AI_MODEL_2_DATA_CONFIG,
        .ai_get_report = ai_model_2_get_report,
        .ai_create = ai_model_2_create,
        .ai_destroy = ai_model_2_destroy,
        .ai_get_error = ai_model_2_get_error,
        .ai_init = ai_model_2_init,
        .ai_run = ai_model_2_run,
        .ai_forward = ai_model_2_forward,
        .ai_data_params_get = ai_model_2_data_params_get,
        .activations = data_activations1
    },
};

struct network_instance {
     const ai_network_entry_t *entry;
     ai_handle handle;
     ai_network_params params;
};

/* Number of instance is aligned on the number of network */
AI_STATIC struct network_instance gnetworks[AI_MNETWORK_NUMBER] = {0};

AI_DECLARE_STATIC
ai_bool ai_mnetwork_is_valid(const char* name,
        const ai_network_entry_t *entry)
{
    if (name && (strlen(entry->name) == strlen(name)) &&
            (strncmp(entry->name, name, strlen(entry->name)) == 0))
        return true;
    return false;
}

AI_DECLARE_STATIC
struct network_instance *ai_mnetwork_handle(struct network_instance *inst)
{
    for (int i=0; i<AI_MNETWORK_NUMBER; i++) {
        if ((inst) && (&gnetworks[i] == inst))
            return inst;
        else if ((!inst) && (gnetworks[i].entry == NULL))
            return &gnetworks[i];
    }
    return NULL;
}

AI_DECLARE_STATIC
void ai_mnetwork_release_handle(struct network_instance *inst)
{
    for (int i=0; i<AI_MNETWORK_NUMBER; i++) {
        if ((inst) && (&gnetworks[i] == inst)) {
            gnetworks[i].entry = NULL;
            return;
        }
    }
}

AI_API_ENTRY
const char* ai_mnetwork_find(const char *name, ai_int idx)
{
    const ai_network_entry_t *entry;

    for (int i=0; i<AI_MNETWORK_NUMBER; i++) {
        entry = &networks[i];
        if (ai_mnetwork_is_valid(name, entry))
            return entry->name;
        else {
            if (!idx--)
                return entry->name;
        }
    }
    return NULL;
}

AI_API_ENTRY
ai_error ai_mnetwork_create(const char *name, ai_handle* network,
        const ai_buffer* network_config)
{
    const ai_network_entry_t *entry;
    const ai_network_entry_t *found = NULL;
    ai_error err;
    struct network_instance *inst = ai_mnetwork_handle(NULL);

    if (!inst) {
        err.type = AI_ERROR_ALLOCATION_FAILED;
        err.code = AI_ERROR_CODE_NETWORK;
        return err;
    }

    for (int i=0; i<AI_MNETWORK_NUMBER; i++) {
        entry = &networks[i];
        if (ai_mnetwork_is_valid(name, entry)) {
            found = entry;
            break;
        }
    }

    if (!found) {
        err.type = AI_ERROR_INVALID_PARAM;
        err.code = AI_ERROR_CODE_NETWORK;
        return err;
    }

    if (network_config == NULL)
        err = found->ai_create(network, found->config);
    else
        err = found->ai_create(network, network_config);
    if ((err.code == AI_ERROR_CODE_NONE) && (err.type == AI_ERROR_NONE)) {
        inst->entry = found;
        inst->handle = *network;
        *network = (ai_handle*)inst;
    }

    return err;
}

AI_API_ENTRY
ai_handle ai_mnetwork_destroy(ai_handle network)
{
    struct network_instance *inn;
    inn =  ai_mnetwork_handle((struct network_instance *)network);
    if (inn) {
        ai_handle hdl = inn->entry->ai_destroy(inn->handle);
        if (hdl != inn->handle) {
            ai_mnetwork_release_handle(inn);
            network = AI_HANDLE_NULL;
        }
    }
    return network;
}

AI_API_ENTRY
ai_bool ai_mnetwork_get_report(ai_handle network, ai_network_report* report)
{
    struct network_instance *inn;
    inn =  ai_mnetwork_handle((struct network_instance *)network);
    if (inn)
        return inn->entry->ai_get_report(inn->handle, report);
    else
        return false;
}

AI_API_ENTRY
ai_error ai_mnetwork_get_error(ai_handle network)
{
    struct network_instance *inn;
    ai_error err;
    err.type = AI_ERROR_INVALID_PARAM;
    err.code = AI_ERROR_CODE_NETWORK;

    inn =  ai_mnetwork_handle((struct network_instance *)network);
    if (inn)
        return inn->entry->ai_get_error(inn->handle);
    else
        return err;
}

AI_API_ENTRY
ai_bool ai_mnetwork_init(ai_handle network)
{
    struct network_instance *inn;
    ai_network_params par;

    inn =  ai_mnetwork_handle((struct network_instance *)network);
    if (inn) {
        inn->entry->ai_data_params_get(&par);
        for (int idx=0; idx < par.map_activations.size; idx++)
          AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&par.map_activations, idx, inn->entry->activations[idx]);
        return inn->entry->ai_init(inn->handle, &par);
    }
    else
        return false;
}

AI_API_ENTRY
ai_i32 ai_mnetwork_run(ai_handle network, const ai_buffer* input,
        ai_buffer* output)
{
    struct network_instance* inn;
    inn =  ai_mnetwork_handle((struct network_instance *)network);
    if (inn)
        return inn->entry->ai_run(inn->handle, input, output);
    else
        return 0;
}

AI_API_ENTRY
ai_i32 ai_mnetwork_forward(ai_handle network, const ai_buffer* input)
{
    struct network_instance *inn;
    inn =  ai_mnetwork_handle((struct network_instance *)network);
    if (inn)
        return inn->entry->ai_forward(inn->handle, input);
    else
        return 0;
}

AI_API_ENTRY
 int ai_mnetwork_get_private_handle(ai_handle network,
         ai_handle *phandle,
         ai_network_params *pparams)
 {
     struct network_instance* inn;
     inn =  ai_mnetwork_handle((struct network_instance *)network);
     if (inn && phandle && pparams) {
         *phandle = inn->handle;
         *pparams = inn->params;
         return 0;
     }
     else
         return -1;
 }

#ifdef __cplusplus
}
#endif
