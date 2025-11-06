#include <stdio.h>
#include <string.h>

/*define structure of stock*/
#define MAX_STOCK_COUNT 50
#define STOCK_WORD_LEN 10

/*store data*/
typedef struct {
    char name[STOCK_WORD_LEN];
    int shares;
    double avg_price;
    double current_price;
    double realized_profit;
} Stock;

/*Find stock or find direct access*/
int find_stock_index(Stock stocks[], int count, char *stock_symbol) {
    for(int i = 0; i < count; i++) {
        if (strcmp(stocks[i].name, stock_symbol) == 0)
            return i;
    }
    return -1;
}

void update_stock_price(Stock stocks[], int i, char *action, int quantity, double price) {
    if (strcmp(action, "BUY") == 0) {
        double total_cost = stocks[i].shares * stocks[i].avg_price;
        // If I buy new one
        total_cost += quantity * price;
        stocks[i].shares += quantity;
        stocks[i].avg_price = total_cost/ stocks[i].shares;
        stocks[i].current_price = price;
    }
    else if (strcmp(action, "SELL") == 0) {
        printf("NEWS:\n");
        stocks[i].shares -= quantity;
        // Can't sell more than we own
        if (stocks[i].shares < 0) {
            stocks[i].shares = 0;
        }
        double profit = (price - stocks[i].avg_price) * quantity;
        stocks[i].realized_profit += profit;
        printf("Sold %d %s for profit %.2f\n", quantity, stocks[i].name, profit);
        // Remember the price for recent transaction
        stocks[i].current_price = price;
    }
}

int main() {
    /*Read file from txt*/
    FILE *file = fopen("transaction.txt", "r");
    if (file == NULL) {
        printf("The file is empty or error\n");
        return 1;
    }

    Stock stocks[MAX_STOCK_COUNT];
    int count = 0;
    char stock_symbol[STOCK_WORD_LEN];
    char action[10]; // store 'b''u''y' or 's''e''l''l' and leftover .. soace
    int quantity;
    double price;

    while (fscanf(file, "%s %s %d %lf", stock_symbol, action, &quantity, &price) == 4) {
        int i = find_stock_index(stocks, count, stock_symbol);

        /*If i = -1 then pass the new data to permanent struct value*/
        if (i == -1) {
            strcpy(stocks[count].name, stock_symbol);
            if(strcmp(action, "BUY") == 0) {
                stocks[count].shares = quantity;
                stocks[count].avg_price = price;
            } else {
                stocks[count].shares = 0;
                stocks[count].avg_price = 0.0;
            }
            stocks[count].current_price = price;
            count++;
            /*If i = 0 then just update the variable in update function*/
        } else {
            update_stock_price(stocks, i, action, quantity, price);
        }
    }
        
    fclose(file);

    /*Output format, update stock, and calculate total profit with final holding*/
    printf("\n--------------------------------------------------STOCK PORTFOLIO SUMMARY----------------------------------------\n");
    double total_realized = 0.0;

    for(int i = 0; i < count; i++) {
        total_realized += stocks[i].realized_profit;
        double profit = (stocks[i].current_price - stocks[i].avg_price) * stocks[i].shares;
        printf("Stock: %s | Shares: %d | Avg Price: %.2f | Current Price: %.2f | Unrealized: %.2f\n",
            stocks[i].name, stocks[i].shares, stocks[i].avg_price, stocks[i].current_price, profit);
    }

    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("Total Profit of Stock Sell: %.2f\n", total_realized);
    printf("Note: Unrealized profit (current shares owned * (newest price - average price) is the profit if the client decided to sell\n");
    printf("------------------------------------------------------END-----------------------------------------------------------------\n");
    return 0;
}