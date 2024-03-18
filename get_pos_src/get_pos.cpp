#include <iostream>

#include <vector>
#include <chrono>
//#include <rs_pipeline.h>
#include "realsenselib/rs.hpp"
#include <system_error>
#include <iomanip>
#include <fstream>

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

    std::ofstream myFile("pos_result.csv");
    double time_count = 0.0;
    auto start_time = std::chrono::high_resolution_clock::now();
    myFile << "Time,x,y,z,\n";

    std::cout << "Beginning parsing..." << std::endl;
    for (int n = 0; n < 1000; ++n) {
        
        //auto start_time = std::chrono::high_resolution_clock::now();
        clock_t start_time = clock();
       

        auto frames = pipe.wait_for_frames(); // Wait for next frame from camera
        auto f = frames.first_or_default(RS2_STREAM_POSE); // get frame from pose stream
        auto pose_data = f.as<rs2::pose_frame>().get_pose_data();

       
        
        //auto end_time = std::chrono::high_resolution_clock::now();
        
        //std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;
        
        //time_count += elapsed_time.count();
        
       

        // Plotting logic here
        

        // Print the x, y, z values of the translation, relative to initial position
        std::cout << "\r" << "Device Position: " << std::setprecision(3) << std::fixed << pose_data.translation.x << " " <<
        pose_data.translation.y << " " << pose_data.translation.z << " (meters)" << std::endl;
        std::cout <<"Time count: " << time_count << std::endl;

        myFile << time_count << "," << pose_data.translation.x << "," << pose_data.translation.y << "," << pose_data.translation.z << ",\n";
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
        time_count += elapsed_time;
    }

    std::cout << "Done! Writing to files... WIP" << std::endl;

    // Write pos_matrix and time_datenum to files

    //TO BE IMPLEMENTED

    //End program
    std::cout << "Program successfully finished." << std::endl;

    return 0;
}
