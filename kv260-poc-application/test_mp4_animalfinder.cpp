/*
 * Copyright 2019 Xilinx Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/*
 * 2022-01-13 Zak: 
 *   modified to do batch processing of video file
 */

#include <glog/logging.h>

#include <string>
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "./string_format.hpp"
#include "./detect_stats.hpp"
#include "./local_demo.hpp"
#include <vitis/ai/nnpp/yolov3.hpp>
#include <vitis/ai/yolov3.hpp>


/*
 *   The color loops every 27 times,
 *    because each channel of RGB loop in sequence of "0, 127, 254"
 */
static cv::Scalar getColor(int label) {
  int c[3];
  for (int i = 1, j = 0; i <= 9; i *= 3, j++) {
    c[j] = ((label / i) % 3) * 127;
  }
  return cv::Scalar(c[2], c[1], c[0]);
}

// Result Processor
static cv::Mat process_result(cv::Mat &image,
			      const vitis::ai::YOLOv3Result &result,
			      bool is_jpeg) {
  float quality_of_detect[DS_MAX_BINS];
  float area_of_detect[DS_MAX_BINS];
  
  int i = 0;
    for (const auto bbox : result.bboxes) {
    int label = bbox.label;
    float xmin = bbox.x * image.cols + 1;
    float ymin = bbox.y * image.rows + 1;
    float xmax = xmin + bbox.width * image.cols;
    float ymax = ymin + bbox.height * image.rows;
    float confidence = bbox.score;
    if (xmax > image.cols) xmax = image.cols;
    if (ymax > image.rows) ymax = image.rows;
    LOG_IF(INFO, is_jpeg) << "RESULT: " << label << "\t" << xmin << "\t" << ymin
                          << "\t" << xmax << "\t" << ymax << "\t" << confidence
                          << "\n";
    cv::rectangle(image, cv::Point(xmin, ymin), cv::Point(xmax, ymax),
                  getColor(label), 1, 1, 0);

    if (i < DS_MAX_BINS) {
	quality_of_detect[i] = confidence;
	area_of_detect[i] = bbox.width * bbox.height;
        if (area_of_detect[i] > 1.0) {
	  // if area is larger than 1, we're really confused for some reason
	  area_of_detect[i] = 0.0; 
	}
    }
    i += 1;
  }
  // Accumulate properties of the frame
  g_detect_stats[g_video_index].add_frame(size(result.bboxes), quality_of_detect, area_of_detect);

  return image;
}


// Main event
using namespace std;

int main(int argc, char *argv[]) {
  string model = argv[1];

  return vitis::ai::main_for_video_demo(
      argc, argv, [model] { return vitis::ai::YOLOv3::create(model); },
      process_result, 2);
}


