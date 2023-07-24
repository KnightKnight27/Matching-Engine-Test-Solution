<!-- Instructions for Running the Matching Engine Test Solution on your machine -->
<!-- Linux -->
## Linux

Start by running the `run.sh` file on Linux, follow these steps:

1. Open the terminal.

2. Navigate to the directory `~/Matching-Engine-Test-Solution` where the `run.sh` file is located using the `cd` command. For example:
 
3. Execute the `run.sh` script using the following command: <br>
```sh
sh run.sh
```

<!-- Windows -->
## Windows

To run the `run.sh` file on Windows, follow these steps:

1. Open the Command Prompt or PowerShell.

2. Navigate to the directory  `~/Matching-Engine-Test-Solution` where the `run.sh` file is located using the `cd` command. For example:
```sh
cd C:\~\Matching-Engine-Test-Solution\
```
3.  Execute the `run.sh` script using the following command:
```sh
bash run.sh
```

If you encounter any issues or errors while running the script, make sure that you have the appropriate permissions to execute the script and that the script file is located in the correct directory.

## Approach for Solving

1. A <b>Map Data Structure</b> is used here for both SELL/BUY order types which stores the List of orders we have for each Instrument.
    The choice of Ordered Map could be justified as it keeps the keys sorted in ascneding order hence in our case it is sorting in the Order of Prices.
    We can match any given order by Iterating from beginning to end for Buy type order and vice versa for Sell type orders.
2. Order class has boolean attribute to indicate filledOrders hence at the end we can print orders which were incompletely filled or not filled at all.
