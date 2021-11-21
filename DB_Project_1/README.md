# DB_Project_1 : Why DBMS?
POSTECH Database System Project1

Environments

OS : Ubuntu 14.04 or above
Compiler : g++ 4.7 or above (Please do not use external libraries)
Purpose and Goal 

The purpose of this assignment is primarily three-fold... 

   Firstly, through this assignment it is hoped that you will take the opportunity to familiarize yourself with Linux C++ environment, which you will be using for the more difficult assignments to follow, and the coding style expected and the submission process. 

   Secondly, we would like to introduce you to the types of queries that are regularly asked of Database Management Systems (DBMS), and get you thinking about how the required results are produced in code. 

   Lastly, this assignment is meant to give you a glimpse into what the world would be like without advanced DBMS tools - a good a place as any to begin this course. Welcome to CSED421.

The assignments are designed to complement the material in class, and improve the understand thereof. Make use of this opportunity to explore the subject matter in greater depth.

Outline 

The result of your work for this assignment should be simple C++ programs that will read a given data set from a file, of specified format, and output the correct result (for that given data set) to stdout. In essence, your program will execute a specific "query" on a table of data. The program should accept the filename(s) containing tables of data as its command-line parameter(s).

The data you will be using is an excerpt taken from an example on-line shopping/ordering/delivery system. Therefore, some of the fields in the tables you are given will not make sense in the context of the queries you need to write. However, all the information and tables you need to produce a correct answer are provided.

Query #1: 
List all the last names (LNAME) of the active customers that live in Toronto.

You will be provided with a customer and zonecost tables in separate files. So your program should be executed as : 

<your_binary> q1 <customer.file> <zonecost.file>

ex) ./a.out q1 customer.txt zonecost.txt (on your local directory) 

The order of columns and file format will not change. Below are sample files similar to ones that your programs will be tested against.

customer table 
UNAME                PASSWD               LNAME                FNAME                ADDR                                               ZONE   SEX AGE    LIMIT  BALANCE    CREDITCARD           EMAIL                                              ACTIVE 
-------------------- -------------------- -------------------- -------------------- -------------------------------------------------- ------ --- ------ ------ ---------- -------------------- -------------------------------------------------- ------ 
rimon                rimon                Barr                 Rimon                22 Greenside Cres., Thornhill, ON L3T 6W9          2      m   102    100    -22.13     1234567890           barr@cs.cornell.edu                                1 
vitomik              vitomik              Pupovir              Vitomik              12 Treford Pl., Toronto, ON, M6J 1Z5               1      m   201    100    7.79                            1@cdf.toronto.edu                                  1 
gabe                 gabe                 Belipsky             Gabe                 178 Jarvis, Toronto                                5      m   112    200    8.24                            2@cdf.toronto.edu                                  1 
babas                babas                Khahremanp           Babas                6 Sussex Drive                                     7      m   123    100    43.20      2345678901           3@cdf.toronto.edu                                  1 
inactive             inactive             active               in                   where                                              8      f   321    100    0.00                            inactive@cdf.toronto.edu                           0 
lube                 lube                 Tuik                 Lubeq                downtown                                           1      m   320    100    26.24                           4@cdf                                              1

zonecost table 
ZONEID ZONEDESC             PRICE 
------ -------------------- ------- 
1      Toronto              5.00 
2      North York           7.00 
3      Mississauga          8.00 
4      Etobicoke            8.00 
5      CDF                  0.00 
6      Transylvania         12.00 
7      Atlantis             12.00 
8      Mars                 50.00

sample output 
Pupovir
Tuik

A customer is active if the value of the last field (called `ACTIVE') in the customer table is set to 1. A customer lives in Toronto if the value of the ZONE field matches a value of the ZONEID field in the zonecost table and the corresponding ZONEDESC entry in the zonecost table equals `Toronto'. 

Your program should output one line for each result record of the query, displaying the last name of the customers  only. No other output is required. Be careful not to make any assumptions while writing your program, just to make it easier to write. For example, in the zonecost table, there could be two entries with ZONEDESC Toronto but different values for zoneid.

It is expected that this program will use features available in C++. Use streams for data input and output. Create objects to encapsulate records of each table, and try to make them as self contained as possible. Marks will be awarded for proper class design and encapsulation.

Query #2: 
Output the BARCODE and the PRODDESC for each product that has been purchased by at least two customers. 

In this case you will need the lineitem and products tables, and your program should be executed as: 

<your_binary> q2 <lineitem.file> <products.file>

ex) ./a.out q2 lineitem.txt products_a.txt (on your local directory) 

Shown below is some sample data. You can assume that the BARCODE field is a key for the products table, and you can assume that UNAME uniquely identifies a customer. 

lineitem table 
UNAME                DATE       TIME     BARCODE              QUANTITY PRICE 
-------------------- ---------- -------- -------------------- -------- --------- 
rimon                04/15/1998 16:59:09 1016                 1        2.68 
rimon                04/15/1998 16:59:09 1023                 3        2.15 
vitomik              04/15/1998 17:02:34 1013                 2        1.49 
vitomik              04/15/1998 17:02:34 1023                 3        2.15 
vitomik              04/15/1998 17:02:34 1010                 2        5.24 
vitomik              04/15/1998 17:02:34 1007                 2        2.39 
vitomik              04/15/1998 17:02:34 1011                 1        9.95 
vitomik              04/15/1998 17:02:34 1008                 1        3.15 
babas                03/10/1998 17:32:58 1019                 10       3.12 
rimon                04/15/1998 08:00:00 1002                 2        2.56 
rimon                04/15/1998 08:00:00 1008                 5        3.15 
gabe                 04/12/1998 17:40:29 1019                 1        3.12 
gabe                 04/12/1998 17:40:29 1002                 2        2.56 
lube                 04/17/1998 16:22:26 1016                 3        2.68 
lube                 04/17/1998 16:22:26 1023                 5        2.15 
lube                 04/17/1998 16:22:26 1013                 1        1.49 
lube                 04/17/1998 16:22:26 1005                 1        0.96

products table 
BARCODE              PRICE      PRODDESC                                           MFG                  SUPPLIER             TAXABLE CATEGORY             SALE_PERCENT 
-------------------- ---------- -------------------------------------------------- -------------------- -------------------- ------- -------------------- ------------ 
1001                 3.38       Apple juice                                        Oceanspray           XYZ                  1       Beverage             0.00 
1002                 2.56       Orange juice                                       Tropicana            XYZ                  1       Beverage             0.10 
1003                 4.21       Lemonade                                           Oceanspray           XYZ                  1       Beverage             0.00 
1004                 1.35       Chocolate drink                                    Hershey              XYZ                  1       Beverage             0.00 
1005                 0.96       Gatorade                                           Gatorade             XYZ                  1       Beverage             0.00 
1006                 2.99       Milk homogenised 2% 4L                             Dairy Farms          XYZ                  1       Beverage             0.00 
1007                 2.39       Celestial seasonings tea                           Bigelow              XYZ                  1       Beverage             0.20 
1008                 3.15       Special K 12oz                                     Kellogg              XYZ                  1       Cereal               0.00 
1009                 1.85       Oatmeal cereal                                     Quaker               XYZ                  1       Cereal               0.00 
1010                 5.24       Waffles                                            Eggo                 XYZ                  1       Cereal               0.00 
1011                 9.95       Sunflower cooking oil, 34oz                        Crisco               XYZ                  1       Cooking              0.05 
1012                 3.58       Distilled white vinegar                            Crisco               XYZ                  1       Cooking              0.00 
1013                 1.49       Ketchup                                            Heinz                XYZ                  1       Pasta                0.00 
1014                 1.75       Seafood cocktail sauce                             Heinz                XYZ                  1       Cooking              0.00 
1015                 0.98       Pizza sauce                                        Heinz                XYZ                  1       Cooking              0.00 
1016                 2.68       Paprika                                            McCormicj            XYZ                  1       Cooking              0.15 
1017                 1.98       Shake 'n bake chicken                              Quaker               XYZ                  1       Cooking              0.00 
1018                 0.88       Crushed tomatoes                                   Hunts                XYZ                  1       Vegetables           0.00 
1019                 3.12       Dried tomatoes                                     Hunts                XYZ                  1       Vegetables           0.10 
1020                 1.44       Mashed potatoes                                    Hamburger helper     XYZ                  1       Vegetables           0.00 
1021                 5.28       Garlic                                             Hunts                XYZ                  1       Vegetables           0.00 
1022                 2.85       Whole kernel corn                                  Hamburger helper     XYZ                  1       Vegetables           0.00 
1023                 2.15       Spaghetti                                          Hamburger helper     XYZ                  1       Pasta                0.20 
1024                 1.24       Flavoured rice                                     Hamburger helper     XYZ                  1       Pasta                0.00

sample output 
1002    Orange juice
1008    Special K 12oz
1013    Ketchup
1016    Paprika
1019    Dried tomatoes
1023    Spaghetti
