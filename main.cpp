#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

int main()
{
    char enter;
    int arr[6];

    std::cout << " If you are a collector, enter: + " << std::endl;
    std::cout << " If you are a user, enter: - " << std::endl;
    std::cin >> enter;
    if (enter == '+')
    {
        std::srand(std::time(nullptr));
        int banknotes = 1000;

        for (int i = 0;i < 6;i++)
        {
            if (i == 0)arr[i] = (rand() % 40 + 10);
            else if (i == 1)arr[i] = (rand() % 80 + 20);
            else if (i == 2)arr[i] = (rand() % 101 + 80);
            else if (i == 3)arr[i] = (rand() % 150 + 50);
            else if (i == 4)arr[i] = (rand() % 250 + 80);
            else if (i == 5)
            {
                arr[i] = banknotes;
                break;
            }
            banknotes -= arr[i];
        }

        std:: ofstream fileOut("banknotes.bin", std::ios:: out | std::ios::binary);

        if (!fileOut.is_open())
        {
            std::cout << "Error!" << std::endl;
        }
        else
        {
            fileOut.write((const char*) arr, 7 * sizeof(int));
        }
        fileOut.close();

    }
    else
    {
        int many;
        std::cout << "Enter the amount you want to withdraw: " << std::endl;
        std::cin >> many;
        std::ifstream fileIn("banknotes.bin");

        if (!fileIn.is_open())
        {
            std::cout << "Error!" << std::endl;
        }
        else
        {
            fileIn.read((char *) arr, 6 * sizeof(int));
            fileIn.close();

            while (many % 100 != 0)
            {
                std::cout << "ERROR!The amount must be a multiple of 100" << std::endl;
                std::cout << "Enter the amount you want to withdraw: " << std::endl;
                std::cin >> many;
            }
            if ((many / 5000 > 0) || ((many % 5000) / 2000 > 0) || (((many % 5000) % 2000) / 1000 > 0)
                || ((((many % 5000) % 2000) % 1000) / 500 > 0) || (((((many % 5000) % 2000) % 1000) % 500) / 200 > 0)
                || ((((((many % 5000) % 2000) / 1000) % 500) % 200) / 100 > 0) || many == 100)
            {
                if (arr[0] >= many / 5000)
                {
                    arr[0] -= many / 5000;
                    many %= 5000;
                }
                if (arr[1] >= many / 2000)
                {
                    arr[1] -= many / 2000;
                    many %= 2000;
                }

                if (arr[2] >= many / 1000)
                {
                    arr[2] -= many / 1000;
                    many %= 1000;
                }
                if (arr[3] >= many / 500)
                {
                    arr[3] -= many / 500;
                    many %= 500;
                }
                if (arr[4] >= many / 200)
                {
                    arr[4] -= many / 200;
                    many %= 200;
                }

                if (arr[5] >= many / 100)
                {
                    arr[5] -= many / 100;
                    many %= 100;
                }
                else
                {
                    std::cout << "ERROR!The operation is impossible";
                }
            }

            std:: ofstream fileOut("banknotes.bin", std::ios:: out | std::ios::binary);
            if (!fileOut.is_open())
            {
                std::cout << "Error!" << std::endl;
            }
            else
            {
                fileOut.write((const char*) arr, 6 * sizeof(int));
            }
            fileOut.close();
        }
    }
    return 0;
}
