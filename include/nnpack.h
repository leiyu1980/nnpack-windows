#pragma once

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#include <cstdbool>
#else
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#endif

#include "pthreadpool.h"

enum nnp_status 
{
	nnp_status_success = 0,
	
	nnp_status_invalid_batch_size = 2,
	nnp_status_invalid_channels = 3,
	nnp_status_invalid_input_channels = 4,
	nnp_status_invalid_output_channels = 5,
	nnp_status_invalid_input_size = 10,
	nnp_status_invalid_input_stride = 11,
	nnp_status_invalid_input_padding = 12,
	nnp_status_invalid_kernel_size = 13,
	nnp_status_invalid_pooling_size = 14,
    nnp_status_invalid_pooling_stride = 15,
	nnp_status_invalid_algorithm = 16,
	nnp_status_invalid_transform_strategy = 17,
	nnp_status_invalid_output_subsampling = 13,
	nnp_status_invalid_activation = 14,
	nnp_status_invalid_activation_parameters = 15,

	nnp_status_unsupported_input_size = 20,
	nnp_status_unsupported_input_stride = 21,
	nnp_status_unsupported_input_padding = 22,
	nnp_status_unsupported_kernel_size = 23,
	nnp_status_unsupported_pooling_size = 24,
	nnp_status_unsupported_pooling_stride = 25,
	nnp_status_unsupported_algorithm = 26,
	nnp_status_unsupported_transform_strategy = 27,
	nnp_status_unsupported_activation = 28,
	nnp_status_unsupported_activation_parameters = 29,

	nnp_status_uninitialized = 50,
	nnp_status_unsupported_hardware = 51,
	nnp_status_out_of_memory = 52,
	nnp_status_insufficient_buffer = 53,
	nnp_status_misaligned_buffer = 54
};


enum nnp_activation 
{
	nnp_activation_identity = 0,
	nnp_activation_relu = 1,
};

enum nnp_convolution_algorithm 
{
	nnp_convolution_algorithm_auto = 0,
	nnp_convolution_algorithm_ft8x8 = 1,
	nnp_convolution_algorithm_ft16x16 = 2,
	nnp_convolution_algorithm_wt8x8 = 3,
	nnp_convolution_algorithm_implicit_gemm = 4,
	nnp_convolution_algorithm_direct = 5
};

enum nnp_convolution_transform_strategy 
{
	nnp_convolution_transform_strategy_compute = 1,
	nnp_convolution_transform_strategy_precompute = 2,
	nnp_convolution_transform_strategy_reuse = 3
};

/* For backward compatibility */
#define nnp_convolution_transform_strategy_block_based nnp_convolution_transform_strategy_compute
#define nnp_convolution_transform_strategy_tuple_based nnp_convolution_transform_strategy_compute

struct nnp_size 
{
	size_t width;
	size_t height;
};
	
struct nnp_padding 
{
	size_t top;
	size_t right;
	size_t bottom;
	size_t left;
};

struct nnp_workspace_pointers
{
	void* kernel;
	void* input;
	void* output;
};

enum nnp_status nnp_initialize();

enum nnp_status nnp_deinitialize();

enum nnp_status nnp_convolution_output(
	enum nnp_convolution_algorithm algorithm,
	const size_t batch_size,
	const size_t input_channels,
	const size_t output_channels,
	const struct nnp_size input_size,
	const struct nnp_padding input_padding,
	const struct nnp_size kernel_size,
	const float* input,
	const float* kernel,
	const float* bias,
	float* output,
	nnp_workspace_pointers* workspace_buffer);

	
enum nnp_status nnp_convolution_input_gradient(
	enum nnp_convolution_algorithm algorithm,
	const size_t batch_size,
	const size_t input_channels,
	const size_t output_channels,
	const struct nnp_size input_size,
	const struct nnp_padding input_padding,
	const struct nnp_size kernel_size,
	const float* grad_output,
	const float* kernel,
	float* grad_input,
	nnp_workspace_pointers* workspace_buffer);

enum nnp_status nnp_convolution_kernel_gradient(
	enum nnp_convolution_algorithm algorithm,
	const size_t batch_size,
	const size_t input_channels,
	const size_t output_channels,
	const struct nnp_size input_size,
	const struct nnp_padding input_padding,
	const struct nnp_size kernel_size,
	const float* input,
	const float* grad_output,
	float* grad_kernel,
	nnp_workspace_pointers* workspace_buffer);

	
enum nnp_status nnp_convolution_inference(
	enum nnp_convolution_algorithm algorithm,
	enum nnp_convolution_transform_strategy transform_strategy,
	const size_t input_channels,
	const size_t output_channels,
	const struct nnp_size input_size,
	const struct nnp_padding input_padding,
	const struct nnp_size kernel_size,
	const struct nnp_size output_subsampling,
	const float* input,
	const float* kernel,
	const float* bias,
	float* output);

enum nnp_status nnp_fully_connected_output(
	const size_t batch_size,
	const size_t input_channels,
	const size_t output_channels,
	const float* input,
	const float* kernel,
	float* output);

enum nnp_status nnp_fully_connected_inference(
	const size_t input_channels,
	const size_t output_channels,
	const float* input,
	const float* kernel,
	float* output);

enum nnp_status nnp_max_pooling_output(
	const size_t batch_size,
	const size_t channels,
	const struct nnp_size input_size,
	const struct nnp_padding input_padding,
	const struct nnp_size pooling_size,
	const struct nnp_size pooling_stride,
	const float* input,
	float* output);

enum nnp_status nnp_softmax_output(
	const size_t batch_size,
	const size_t channels,
	const float* input,
	float* output);

enum nnp_status nnp_relu_output(
	const size_t batch_size,
	const size_t channels,
	const float* input,
	float* output,
	float negative_slope);

enum nnp_status nnp_relu_input_gradient(
	const size_t batch_size,
	const size_t channels,
	const float* grad_output,
	const float* input,
	float* grad_input,
	float negative_slope);
