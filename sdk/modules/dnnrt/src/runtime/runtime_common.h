/****************************************************************************
 * modules/dnnrt/src/runtime/runtime_common.h
 *
 *   Copyright 2018 Sony Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Sony Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef RUNTIME_COMMON_H
#  define RUNTIME_COMMON_H

#  include <sdk/config.h>
#  include <errno.h>
#  include <nnablart/functions.h>
#  include <nnablart/runtime.h>

#  ifdef __cplusplus
extern "C"
{
#  endif

#  define DNN_PRINT(...) printf(__VA_ARGS__)

#  define DNN_CHECK_NULL(b)                                                      \
  do {                                                                         \
    if ((b) == NULL) {                                                         \
      DNN_PRINT("Null-check failed. %s()@%s:L%d\n", __FUNCTION__, __FILE__,    \
                __LINE__);                                                     \
      return;                                                                  \
    }                                                                          \
  } while (0)
#  define DNN_CHECK_NULL_RET(b, r)                                               \
  do {                                                                         \
    if ((b) == NULL) {                                                         \
      DNN_PRINT("Null-check failed. %s()@%s:L%d\n", __FUNCTION__, __FILE__,    \
                __LINE__);                                                     \
      return r;                                                                \
    }                                                                          \
  } while (0)
#  define DNN_CHECK_NULL_GOTO(b, go)                                             \
  do {                                                                         \
    if ((b) == NULL) {                                                         \
      DNN_PRINT("Null-check failed. %s()@%s:L%d\n", __FUNCTION__, __FILE__,    \
                __LINE__);                                                     \
      goto go;                                                                 \
    }                                                                          \
  } while (0)
#  define DNN_CHECK_FUNC_RET(f)                                                  \
  do {                                                                         \
    int err = -EPERM;                                                          \
    if ((err = (f)) != 0) {                                                    \
      DNN_PRINT("Function-check failed. %s()@%s:L%d\n", __FUNCTION__,          \
                __FILE__, __LINE__);                                           \
      return err;                                                              \
    }                                                                          \
  } while (0)
#  define DNN_CHECK_FUNC(f)                                                      \
  do {                                                                         \
    if ((f) != 0) {                                                            \
      DNN_PRINT("Function-check failed. %s()@%s:L%d\n", __FUNCTION__,          \
                __FILE__, __LINE__);                                           \
      return;                                                                  \
    }                                                                          \
  } while (0)
#  define DNN_CHECK_FUNC_GOTO(f, go)                                             \
  do {                                                                         \
    int err = -EPERM;                                                          \
    if ((err = (f)) != 0) {                                                    \
      DNN_PRINT("Function-check failed. %s()@%s:L%d\n", __FUNCTION__,          \
                __FILE__, __LINE__);                                           \
      goto go;                                                                 \
    }                                                                          \
  } while (0)
#  define CHECK_FUNC_RET_VAL(f, val)                                             \
  do {                                                                         \
    int err = -EPERM;                                                          \
    if ((err = (f)) != 0) {                                                    \
      DNN_PRINT("Function-check failed. %s()@%s:L%d\n", __FUNCTION__,          \
                __FILE__, __LINE__);                                           \
      return val;                                                              \
    }                                                                          \
  } while (0)
#  define CHECK_FUNC_ERR_RET(f)                                                  \
  do {                                                                         \
    int err = 0;                                                               \
    if ((err = (f)) < 0) {                                                     \
      DNN_PRINT("Function-check failed. %s()@%s:L%d\n", __FUNCTION__,          \
                __FILE__, __LINE__);                                           \
      return NG;                                                               \
    }                                                                          \
  } while (0)

  typedef struct dnn_global_context
    {
      int rt_count;
      int req_scratch_buf_bsize;
      int scratch_buf_bsize;
      void *scratch_buf;
    } dnn_global_context;

  rt_function_error_t dnnrt_exec_convolution(rt_function_t * f);
  rt_function_error_t dnnrt_exec_affine(rt_function_t * f);
  rt_return_value_t dnnrt_affine_alloc(nn_network_t * net,
                                       void *function_context);
  rt_return_value_t dnnrt_convolution_alloc(nn_network_t * net,
                                            void *function_context);

  void dnn_req_scratch_buf(int size);
  void *dnn_scratch_buf(void);

#  ifdef __cplusplus
}
#  endif

#endif                          /* RUNTIME_COMMON_H */
