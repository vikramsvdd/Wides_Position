#include <iostream>

#include <vector>
#include <chrono>
//#include <rs_pipeline.h>
#include "realsenselib/rs.hpp"
#include <system_error>
#include <iomanip>

int main() {
    std::cout << "Please press any key to begin data collection" << std::endl;
    std::cin.get();
    
    std::cout << "Beginning data collection..." << std::endl;
    rs2::pipeline pipe;
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
    pipe.start(cfg);
    std::cout << "Pipeline successfully started" << std::endl;

    std::vector<std::array<float, 3>> pos_matrix(1000);
    std::vector<float> time_datenum(1000);

    auto start_time = std::chrono::steady_clock::now();

    std::cout << "Beginning parsing..." << std::endl;
    for (int n = 0; n < 1000; ++n) {
        

        auto frames = pipe.wait_for_frames(); // Wait for next frame from camera
        auto f = frames.first_or_default(RS2_STREAM_POSE); // get frame from pose stream
        auto pose_data = f.as<rs2::pose_frame>().get_pose_data();

        //was previously pose.translation
        pos_matrix[n][0] = pose_data.translation.x;
        pos_matrix[n][1] = pose_data.translation.y;
        pos_matrix[n][2] = pose_data.translation.z;

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        time_datenum[n] = elapsed_time;

        // Plotting logic here
        // Print the x, y, z values of the translation, relative to initial position
        std::cout << "\r" << "Device Position: " << std::setprecision(4) << std::fixed << pose_data.translation.x << " " <<
        pose_data.translation.y << " " << pose_data.translation.z << " (meters)";

    }

    std::cout << "Done! Writing to files..." << std::endl;

    // Write pos_matrix and time_datenum to files


    //End program
    std::cout << "Program successfully finished." << std::endl;

    return 0;
}
