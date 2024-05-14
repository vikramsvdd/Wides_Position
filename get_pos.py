import time
import csv
import pyrealsense2 as rs

LOOP_LIM = 1000

print("T265 Pose - Matrix ver.")
input("Please press any key to begin data collection")

print("Beginning data collection...")
pipe = rs.pipeline()
cfg = rs.config()
cfg.enable_stream(rs.stream.pose, rs.format.xyz32f)
profile = pipe.start(cfg)
print("Pipeline successfully started")

pos_matrix = []

with open("pos_result.csv", mode='w', newline='') as myFile:
    writer = csv.writer(myFile)
    writer.writerow(['Time', 'x', 'y', 'z'])

    print("Beginning parsing...")
    start_time = time.time()
    for _ in range(LOOP_LIM):
        frames = pipe.wait_for_frames()  # Wait for next frame from camera
        pose = frames.get_pose_frame()
        if pose:
            pose_data = pose.get_pose_data()

            # Put values into a matrix
            pos_matrix_item = [
                time.time() - start_time,
                pose_data.translation.x,
                pose_data.translation.y,
                pose_data.translation.z
            ]
            pos_matrix.append(pos_matrix_item)

            # Print the x, y, z values of the translation, relative to initial position
            print(f"\rDevice Position: {pose_data.translation.x:.4f} {pose_data.translation.y:.4f} {pose_data.translation.z:.4f} (meters)")

    print("Done! Writing to files...")
    writer.writerows(pos_matrix)

print("Program successfully finished.")
