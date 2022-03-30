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

DN_SRC_DIR=/home/robert_zak/GoogleDrive/Models/yolov3_ct_1000/
DN_WT_FILE=yolov3_training_final.weights
DN_CFG_FILE=yolov3_testing.cfg

# Given a Darknet weights, produces .prototxt and .caffemodel
python /opt/vitis_ai/conda/envs/vitis-ai-caffe/bin/convert.py darknet/${DN_CFG_FILE} darknet/${DN_WT_FILE} ct/yolov3.prototxt ct/yolov3.caffemodel
