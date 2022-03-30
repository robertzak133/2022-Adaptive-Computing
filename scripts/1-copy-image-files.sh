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

IMG_SRC_DIR=/home/robert_zak/GoogleDrive/WBWL2020/res608/validation/
IMG_DEST_DIR=images/
CALIB_DIR=ct/
CALIB_FILE=calib.txt
TEST_FILE=caffe_test.txt

rm ${IMG_DEST_DIR}*.jpg

# Copy the Model and Config Files to local darknet directory
cp ${IMG_SRC_DIR}*.jpg ${IMG_DEST_DIR}
# Create file with list of images and labels
(cd ${IMG_DEST_DIR} && ls -1 *.jpg) > ${CALIB_DIR}${CALIB_FILE}
# add the zero because parser is expecting it
sed -i 's/$/ 0/' ${CALIB_DIR}${CALIB_FILE}

# Create file with list of images
ls -1 ${IMG_DEST_DIR}*.jpg > ${CALIB_DIR}${TEST_FILE}
