
/**
 * @mainpage CIT CLIENT
 * @authors Seher Deliballı (seher.kavsur@pavotek.com.tr)
 * @date 09.09 .2023
 *
 * @copyright PAVO
 */
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <ctime>
#include <memory>
#include "../include/common.h"
#include "../include/citHandler.h"

struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                {"version", no_argument, NULL, 'v'},
                                {"master", optional_argument, NULL, 'A'},
                                {"slave", optional_argument, NULL, 'S'},
                                {"critical", optional_argument, NULL, 'c'},
                                {"major", optional_argument, NULL, 'o'},
                                {"minor", optional_argument, NULL, 'i'},
                                {"medium", optional_argument, NULL, 'e'},
                                {NULL, 0, NULL, 0}};
int main(int argc, char **argv)
{
    using namespace std;
    int lRetStatus = 0;
    int argOpt = 0;
    int long_index = 0;
    int master = 0;
    int slave = 0;
    

    time_t now = time(0);
    char* dt = ctime(&now);
    printf("CLIENT Build date: %s", dt);


    if (argc > 1 && argc <= CMD_LINE_MAX_ARG_NUMBERS)
    {
        while ((argOpt = getopt_long(argc, argv, ":hvAaSsCcOoIiEe", long_options, &long_index)) != -1)
        {
            switch (argOpt)
            {
            case 'h':
                printf("****************************************************************************************"
                       "*******"
                       "**\n");
                printf("@@ use --help, -h to display help section @@\n");
                printf("@@ use --version, -v to display version of program @@\n");
                printf("@@ use --master, -A, -a to run program in SIP Master. @@\n\n");
                printf("@@ |@@| ACHTUNG! The program should be run with master mode in the second SIP Server to "
                       "manage "
                       "the "
                       "redundancy process. @@\n\n");
                printf("@@ use --slave , -S,-s to run program in SIP Slave @@\n");
                printf("@@ |@@| ACHTUNG! The program should be run with slave mode in the first SIP Server to "
                       "join the "
                       "redundancy process. @@\n");
                printf("@@ use --medium , -E,-e to run program with medium debug open @@\n");
                printf("@@ use --major , -O,-o to run program with major debug open @@\n");
                printf("@@ use --minor , -I,-i to run program with minor debug open @@\n");
                printf("@@ use --critical , -C,-c to run program with critical debug open @@\n\n");
                printf("@@ |@@| ACHTUNG! The program can run with many debug mode open! ex: ./prog_name --master "
                       "--medium --major . @@\n");
                printf("****************************************************************************************"
                       "*******"
                       "**\n");
                exit(1);
                break;
            case 'v':
                printf("@@@ version : %s @@@\n", VERSION);
                exit(1);
                break;
            case 'c':
            case 'C':
                critical_debug_value = DEBUG_ON;
                printf("@@@ critical debug active @@@\n");
                break;
            case 'O':
            case 'o':
                major_debug_value = DEBUG_ON;
                printf("@@@ major debug active @@@\n");
                break;
            case 'I':
            case 'i':
                minor_debug_value = DEBUG_ON;
                printf("@@@ minor debug active @@@\n");
                break;
            case 'E':
            case 'e':
                medium_debug_value = DEBUG_ON;
                printf("@@@ medium debug active @@@\n");
                break;
            case 'a':
            case 'A':
                printf("@@@  master mode active : @@@\n");
                master = 1;
                break;

            case 's':
            case 'S':
                printf("@@@ slave mode active : @@@\n");
                slave = 1;
                break;
            default:
                printf("There is an argument which is not matched with the list of the "
                       "defined arguments! the program "
                       "will be closed\n");
                exit(-1);
                break;
            }
        }
        if (master && slave)
        {
            printf("Program can not run in two different modes! choose slave or master mode!\n");
            exit(-1);
        }
        else if (master)
        {
            printf("\n@@@ PROGRAM WORKS IN SIP MASTER @@@\n");
            citHandler *citCli = new citHandler(citHandler::e_SIPType::e_master);
            citCli->run();
            // std::shared_ptr<citHandler> citCli = std::make_shared<citHandler>(citHandler::e_master);
            
            std::this_thread::sleep_for(std::chrono::seconds(10));
            
            delete citCli;

        }
        else if (slave)
        {
            printf("\n@@@ PROGRAM WORKS IN SIP SLAVE @@@\n");
        }        
    }
    else
    {
        printf("There should be extra argument to run program ! (see helper)\n");
        exit(-1);
    }

    return lRetStatus;
}
