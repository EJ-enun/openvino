// Copyright (C) 2018-2023 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <vector>
#include <ngraph/op/util/attr_types.hpp>
#include "single_layer_tests/lstm_sequence.hpp"
#include "common_test_utils/test_constants.hpp"

using namespace LayerTestsDefinitions;

namespace {
std::vector<ngraph::helpers::SequenceTestsMode> mode{ngraph::helpers::SequenceTestsMode::CONVERT_TO_TI_MAX_SEQ_LEN_CONST,
                                                     ngraph::helpers::SequenceTestsMode::CONVERT_TO_TI_RAND_SEQ_LEN_CONST,
                                                     ngraph::helpers::SequenceTestsMode::CONVERT_TO_TI_RAND_SEQ_LEN_PARAM,
                                                     ngraph::helpers::SequenceTestsMode::PURE_SEQ_RAND_SEQ_LEN_CONST,
                                                     ngraph::helpers::SequenceTestsMode::PURE_SEQ_RAND_SEQ_LEN_PARAM,
                                                     ngraph::helpers::SequenceTestsMode::PURE_SEQ};
// output values increase rapidly without clip, so use only seq_lengths = 2
std::vector<size_t> seq_lengths_zero_clip{2};
std::vector<size_t> seq_lengths_clip_non_zero{20};
std::vector<size_t> batch{10};
std::vector<size_t> hidden_size{1, 10};
std::vector<size_t> hidden_size_smoke{1};
std::vector<size_t> input_size{10};
std::vector<std::vector<std::string>> activations = {{"relu", "sigmoid", "tanh"}, {"sigmoid", "tanh", "tanh"},
                                                     {"tanh", "relu", "sigmoid"}, {"sigmoid", "sigmoid", "sigmoid"},
                                                     {"tanh", "tanh", "tanh"}, {"relu", "relu", "relu"}};
std::vector<std::vector<std::string>> activations_smoke = {{"relu", "sigmoid", "tanh"}};
std::vector<float> clip{0.f};
std::vector<float> clip_non_zeros{0.7f};
std::vector<ov::op::RecurrentSequenceDirection> direction = {ov::op::RecurrentSequenceDirection::FORWARD,
                                                                 ov::op::RecurrentSequenceDirection::REVERSE,
                                                                 ov::op::RecurrentSequenceDirection::BIDIRECTIONAL
};
std::vector<InferenceEngine::Precision> netPrecisions = {InferenceEngine::Precision::FP32,
                                                         InferenceEngine::Precision::FP16};

INSTANTIATE_TEST_SUITE_P(LSTMSequenceCommonZeroClip, LSTMSequenceTest,
                        ::testing::Combine(
                                ::testing::ValuesIn(mode),
                                ::testing::ValuesIn(seq_lengths_zero_clip),
                                ::testing::ValuesIn(batch),
                                ::testing::ValuesIn(hidden_size),
                                ::testing::ValuesIn(input_size),
                                ::testing::ValuesIn(activations),
                                ::testing::ValuesIn(clip),
                                ::testing::ValuesIn(direction),
                                ::testing::Values(ngraph::helpers::InputLayerType::CONSTANT),
                                ::testing::ValuesIn(netPrecisions),
                                ::testing::Values(ov::test::utils::DEVICE_GPU)),
                        LSTMSequenceTest::getTestCaseName);

INSTANTIATE_TEST_SUITE_P(LSTMSequenceCommonZeroClipNonConstantWRB, LSTMSequenceTest,
                        ::testing::Combine(
                                ::testing::Values(ngraph::helpers::SequenceTestsMode::PURE_SEQ),
                                ::testing::ValuesIn(seq_lengths_zero_clip),
                                ::testing::ValuesIn(batch),
                                ::testing::ValuesIn(hidden_size),
                                ::testing::ValuesIn(input_size),
                                ::testing::ValuesIn(activations),
                                ::testing::ValuesIn(clip),
                                ::testing::ValuesIn(direction),
                                ::testing::Values(ngraph::helpers::InputLayerType::PARAMETER),
                                ::testing::ValuesIn(netPrecisions),
                                ::testing::Values(ov::test::utils::DEVICE_GPU)),
                        LSTMSequenceTest::getTestCaseName);

INSTANTIATE_TEST_SUITE_P(LSTMSequenceCommonClip, LSTMSequenceTest,
                        ::testing::Combine(
                                ::testing::ValuesIn(mode),
                                ::testing::ValuesIn(seq_lengths_clip_non_zero),
                                ::testing::ValuesIn(batch),
                                ::testing::ValuesIn(hidden_size),
                                ::testing::ValuesIn(input_size),
                                ::testing::ValuesIn(activations),
                                ::testing::ValuesIn(clip_non_zeros),
                                ::testing::ValuesIn(direction),
                                ::testing::Values(ngraph::helpers::InputLayerType::CONSTANT),
                                ::testing::ValuesIn(netPrecisions),
                                ::testing::Values(ov::test::utils::DEVICE_GPU)),
                        LSTMSequenceTest::getTestCaseName);

INSTANTIATE_TEST_SUITE_P(smoke_LSTMSequenceCommonClip, LSTMSequenceTest,
                        ::testing::Combine(
                                ::testing::ValuesIn(mode),
                                ::testing::ValuesIn(seq_lengths_clip_non_zero),
                                ::testing::ValuesIn(batch),
                                ::testing::ValuesIn(hidden_size_smoke),
                                ::testing::ValuesIn(input_size),
                                ::testing::ValuesIn(activations_smoke),
                                ::testing::ValuesIn(clip_non_zeros),
                                ::testing::ValuesIn(direction),
                                ::testing::Values(ngraph::helpers::InputLayerType::CONSTANT),
                                ::testing::ValuesIn(netPrecisions),
                                ::testing::Values(ov::test::utils::DEVICE_GPU)),
                        LSTMSequenceTest::getTestCaseName);

}  // namespace
