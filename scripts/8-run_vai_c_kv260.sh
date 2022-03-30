#!/bin/sh
# Copyright 2020 Xilinx Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,_
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
ARCH=/opt/vitis_ai/compiler/arch/DPUCZDX8G/KV260/arch.json;

cp quantized/deploy.prototxt quantized/deployx.prototxt
sed -i '5 s@  transform_param {@#  transform_param {@' quantized/deployx.prototxt
sed -i '6 s@    mirror: false@#    mirror: false@'  quantized/deployx.prototxt
sed -i '7 s@    yolo_height: 416@#    yolo_height: 416@' quantized/deployx.prototxt
sed -i '8 s@    yolo_width: 416@#    yolo_width: 416@' quantized/deployx.prototxt
sed -i '9 s@  }@#  }@' quantized/deployx.prototxt

# and now change alpha (aka "negative_slope") paramter from 0.1 to 0.1015625
sed -i 's/negative_slope: 0.1/negative_slope: 0.1015625/' quantized/deployx.prototxt

vai_c_caffe --prototxt quantized/deployx.prototxt --caffemodel quantized/deploy.caffemodel --arch ${ARCH} --output_dir compiled/ --net_name yolov3_ct --options "{'mode':'normal','save_kernel':''}";
