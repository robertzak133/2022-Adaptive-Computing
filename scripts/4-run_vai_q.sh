#!/bin/sh
# Copyright Robert Zak
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

vai_q_caffe quantize -model ct/yolov3_quant.prototxt -keep_fixed_neuron -calib_iter 100 -weights ct/yolov3.caffemodel -sigmoided_layers layer133-conv,layer144-conv,layer155-conv -output_dir quantized/ -method 1
