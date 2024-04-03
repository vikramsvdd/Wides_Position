function pose = get_pose
clc

disp("Please press any key to begin data collection")
w = waitforbuttonpress;
if w == 1
    disp("Beginning data collection...")
    pipe = realsense.pipeline();
    pipe.start();
    
    disp("Pipeline successfully started")

    pos_matrix = zeros(1000,3);
    Time = datetime({});
    time_datestr = ["0"; "0"];
    time_datenum = [0; 0];
    
    disp("Initial array initialized")
        
    figure;
    
    disp("Beginning parsing...")
    tic;
    for n = 1:1000
        fs = pipe.wait_for_frames();
        % fs.first_or_default(realsense.stream.pose);
        f = fs.first_or_default(realsense.stream.pose);
        pd = f.as('pose_frame');
        pose = pd.get_pose_data;
           
        x(n) = pose.translation(1);
        y(n) = pose.translation(2);
        z(n) = pose.translation(3);
        
            
        %Time(n,1) = datetime("now", "InputFormat","mm:ss.SSS");
        %time_datestr(n,1) = datestr(now,'SS.FFF');

        % time number vector
        %time_datenum(n,1) = str2num(datestr(now, 'SS.FFF'));

        %Remove the rollover
        time_datenum(n,1) = toc

        pos_matrix(n,1)= pose.translation(1);
        pos_matrix(n,2) = pose.translation(2);
        pos_matrix(n,3) = pose.translation(3);
        
            
        
        plot3(x,y,z)
        %xlim([-.5 .5])
        %ylim([-.5 .5])
        %zlim([-.5 .5])
        %     hold on
        xlabel("X-axis")
        ylabel("Y-Axis")
        zlabel("Z-Axis")
        drawnow;
    end
    disp("Done! Writing to files...")    
    colNames = {'X', 'Y', 'Z'};
        
        
    % Create a table of position matrix values
    pos_table = array2table(pos_matrix, "VariableNames",colNames); 
        
    %create a csv of the position matrix
    %csvwrite("pos_matrix",pos_matrix);
        
    %make an excel file of the table
    %writetable(pos_table,"pos_table","FileType","spreadsheet");
        
    %convert string array to table 
    colStrName = {'Time'};
    pos_DateStrVector = array2table(time_datenum, "VariableNames",colStrName);
        
    %join original table to time_datestr
    pos_DateStrTable = [pos_DateStrVector pos_table];
        
    %make an excel file of the table
    writetable(pos_DateStrTable, "pos_DateStrTable", "FileType","spreadsheet");
        
    % convert table to timetable, with Time as the time vector 
    %pos_timetable = table2timetable(pos_table,"RowTimes", Time);
        
    %create the excel file of the timetable
   
    %writetimetable(pos_timetable, "pos_timetable", "FileType","spreadsheet");
    
    %Make a new table of the differences of another table
    datenumDiff = diff(time_datenum);

    %Make cdf plot of timetable data

    %Ltime = length(time_datenum)
    %LCDF = length(timeCDF)

    
    

    plot3(x,y,z)
    %xlim([-.5 .5])
    %ylim([-.5 .5])
    %zlim([-.5 .5])
    xlabel("X-axis")
    ylabel("Y-Axis")
    zlabel("Z-Axis")

    figure
    cdfplot(datenumDiff);

    disp("Program successfully finished. ")
end
end