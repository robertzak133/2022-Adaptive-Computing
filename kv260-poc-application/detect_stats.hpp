//
// detect_stats.hpp
//
//      object to hold detection statistics


// [N] is frames with N or more detects

// Max number of bins to track
#define DS_MAX_BINS 4

class DetectStats {

private:
  int c_frame_id;
  int c_detects[DS_MAX_BINS];
  int c_highest_quality_frame_id;
  float c_max_quality;
  float c_sum_quality;
  int c_largest_area_frame_id = -1;
  float c_max_area = 0.0;
  float c_sum_area = 0.0;
  std::chrono::steady_clock::time_point c_start_time;
  std::chrono::steady_clock::time_point c_end_time;

public: 
  void init(void) {
    c_frame_id = 0;
    for (int i = 0; i < DS_MAX_BINS; i++) {
      c_detects[i] = 0;
    }
    c_highest_quality_frame_id = -1;
    c_max_quality = 0.0;
    c_sum_quality = 0.0;
    // Keep track of the biggest detection (area wise)
    c_largest_area_frame_id = -1;
    c_max_area = 0.0;
    c_sum_area = 0.0;

    c_start_time = std::chrono::steady_clock::now();

  }

  DetectStats(void) {
    init();
  }

  
  void add_frame(int detects_in_frame, float *quality_of_detect, float *area_of_detect) {
    for (int i = 0; i <= detects_in_frame; i++) {
      if (i >= DS_MAX_BINS) break;
      c_detects[i] += 1;
      if ((quality_of_detect[i] > 0.0) && (quality_of_detect[i] < 1.0)) {
	c_sum_quality += quality_of_detect[i];
	if (quality_of_detect[i] > c_max_quality) {
	  c_highest_quality_frame_id = c_frame_id;
	  c_max_quality = quality_of_detect[i];
	  std::cout << string_format("Add Frame: new max quality in frame %d, index %d of %0.3f\n", c_frame_id, i, quality_of_detect[i]);
	}
      }
      if ((area_of_detect[i] > 0.0) && (area_of_detect[i] < 1.0)) {
	c_sum_area +=  area_of_detect[i];
	if (area_of_detect[i] > c_max_area) {
	  c_largest_area_frame_id = c_frame_id;
	  c_max_area = area_of_detect[i];
	  std::cout << string_format("Add Frame: new max area in frame %d, index %d of %0.3f\n", c_frame_id, i, area_of_detect[i]);
	}
      }
    }
    c_frame_id += 1;
  }

  // Accessors

  int get_frame_id() {
    return c_frame_id;
  }
  
  int get_highest_quality_frame_id (void) {
    return c_highest_quality_frame_id;
  }
  
  float get_max_quality (void) {
    return c_max_quality;
  }

  float get_mean_quality (void) {
    if (c_detects[0] > 0) {
      return (c_sum_quality / (float)c_detects[0]);
    } else {
      return 0.0;
    }
  }

  int get_largest_area_frame_id (void) {
    return c_largest_area_frame_id;
  }
  
  float get_max_area (void) {
    return c_max_area;
  }

  float get_mean_area (void) {
    if (c_detects[0] > 0) {
      return (c_sum_area / (float)c_detects[0]);
    } else {
      return 0.0;
    }
  }

  void print_summary (void) {
    c_end_time = std::chrono::steady_clock::now();
    float duration = (float) std::chrono::duration_cast<std::chrono::milliseconds>(c_end_time - c_start_time)
      .count();

    float average_fps = 1000.0f * (float)c_frame_id / duration;
    
    std::cout << string_format("DetectStats::print_summary: video of %d frames; %0.2f FPS\n", c_frame_id, average_fps);
    
    for (int i = 0; i < DS_MAX_BINS; i++) {
      std::cout << string_format("  >= %d: %d \n", i, c_detects[i]);
    }
    std::cout << string_format("Highest Quality Frame ID: %d\n", c_highest_quality_frame_id);
    std::cout << string_format("Max Quality             : %0.3f\n", c_max_quality);
    std::cout << string_format("Average Quality         : %0.3f\n", get_mean_quality());
    std::cout << string_format("Largest Area    Frame ID: %d\n",    c_largest_area_frame_id);
    std::cout << string_format("Max Area                : %0.3f\n", c_max_area);
    std::cout << string_format("Average Area            : %0.3f\n", get_mean_area());
  }
};
