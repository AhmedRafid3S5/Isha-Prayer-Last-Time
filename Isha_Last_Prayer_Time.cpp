#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    // URL of the webpage
    std::string url = "https://www.islamicfinder.org/world/bangladesh/1185241/dhaka-prayer-times/"; //chnange url here with your location's url

    // Create a file stream to store the webpage content
    std::ofstream webpageFile("webpage.html");

    if (!webpageFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return 1;
    }

    // Use system command to fetch the webpage content and write it to the file
    std::string command = "curl -s -o webpage.html " + url;
    if (system(command.c_str()) != 0) {
        std::cerr << "Failed to fetch the webpage." << std::endl;
        webpageFile.close();
        return 1;
    }

    webpageFile.close();

    // Open the downloaded file for parsing
    std::ifstream file("webpage.html");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return 1;
    }

    std::string line;
    std::string content;
    while (std::getline(file, line)) {
        content += line;
    }
    file.close();

    // Find the positions of "Fajar Prayer Time" and "Maghrib Prayer Time"
    size_t fajarPos = content.find("Fajar Prayer Time");
    size_t maghribPos = content.find("Isha Prayer Prayer Time");
    std::string fajarTime;
    std::string maghribTime;
    if (fajarPos != std::string::npos && maghribPos != std::string::npos) {
        // Extract the Fajar and Maghrib times
        fajarTime = content.substr(fajarPos + 17, 9); // Assuming the time format is HH:MM AM/PM
        maghribTime = content.substr(maghribPos + 23, 9);

        std::cout << "Fajar Prayer Time: " << fajarTime << std::endl;
        std::cout << "Isha Prayer Time: " << maghribTime << std::endl;
    } else {
        std::cerr << "Fajar and Maghrib times not found in the webpage content." << std::endl;
    }
    
     int mh,mm,fh,fm; //mh = maghrib hour mm = maghrib minute fh = fajr hour fm = fajr minute

     fh = (fajarTime[1]-'0')*10 + (fajarTime[2]-'0');
     fm = (fajarTime[4]-'0')*10 + (fajarTime[5]-'0');
     
     mh = (((maghribTime[1]-'0')*10 + (maghribTime[2]-'0'))+12)%24;
     mm = (maghribTime[4]-'0')*10 + (maghribTime[5]-'0');

    int last_time= ((60*mh+mm)+(60*fh+fm))/2;
    int ih= last_time/60;
    int im= last_time%60;

    if(ih>=12 && im<10)
        printf("Isha last time is : %d:0%d am",ih,im);

    else if (ih>=12 && im>10)
        printf("Isha last time is : %d:%d am",ih,im);

    else if(ih<12 && im<10)
        printf("Isha last time is : %d:0%d pm",ih,im);

    else
        printf("Isha last time is : %d:%d pm",ih,im);

    
     
    std::cout<<"\nPress E to close\n";
    char c;
    std::cin>>c;
}
