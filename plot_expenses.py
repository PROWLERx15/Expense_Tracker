import matplotlib.pyplot as plt
from datetime import datetime

# Read expenses from file
with open("Expenses.txt", "r") as file:
    expenses = file.readlines()
    expenses.pop(0)  # Remove header

# Extract expense names and amounts
category_name = [expense.split()[-2] for expense in expenses]
expense_amounts = [float(expense.split()[-1]) for expense in expenses]
cat_dict={}
for i in range(len(category_name)):
    if category_name[i] not in cat_dict.keys():
        cat_dict[category_name[i]]=expense_amounts[i]
    else:
        cat_dict[category_name[i]]+=expense_amounts[i]

# Calculate total expense
total_expense = sum(expense_amounts)
category_name=list(cat_dict.keys())
expense_amounts2=list(expense_amounts)
expense_amounts=list(cat_dict.values())
# Calculate percentage for each expense category
percentages = [(amount / total_expense) * 100 for amount in expense_amounts]

# Plot expenses as a pie chart
plt.figure(figsize=(8, 8))
plt.pie(percentages, labels=category_name, autopct='%1.1f%%', startangle=140)
plt.axis('equal')
plt.title('Expense Distribution')
plt.legend()
plt.show()

with open("Budget.txt","r") as file:
    budget=file.readlines()
    budget.pop(0)
    budget.pop(0)
    

bud=[float(b.split()[0]) for b in budget]
date_budget=[b.split()[-1] for b in budget]
date_exp=[e.split()[-3] for e in expenses]
# Example: ["100 2024-04-01", "200 2024-04-01", "150 2024-04-02"]

budget_dict = {}
expense_dict={}

# Iterate over each budget entry and update the budget dictionary
for entry in range(len(expense_amounts2)):
    amount=expense_amounts2[entry]
    date=date_exp[entry]
    if date in expense_dict:
        # If the date already exists in the dictionary, add the amount to the existing value
        expense_dict[date] += float(amount)
    else:
        # If the date doesn't exist in the dictionary, initialize it with the amount
        expense_dict[date] = float(amount)

expense_dict = dict(sorted(expense_dict.items(),key=lambda x: datetime.strptime(x[0], '%d-%m-%Y')))
e_dates = list(expense_dict.keys())
expense_amounts=list(expense_dict.values())
# Calculate cumulative expenses
cumulative_expenses = [sum(expense_amounts[:i+1]) for i in range(len(expense_amounts))]

for entry in range(len(bud)):
    amount=bud[entry]
    date=date_budget[entry]
    budget_dict[date] = float(amount)

budget_dict = dict(sorted(budget_dict.items(),key=lambda x: datetime.strptime(x[0], '%d-%m-%Y')))
b_dates = list(budget_dict.keys())
budget_amounts = list(budget_dict.values())

# Plot the budget by date as a line graph
plt.plot(b_dates, budget_amounts, label="Budget",marker='o', color='b', linestyle='-')
plt.plot(e_dates, cumulative_expenses, label="Expense",marker='o', color='g', linestyle='-')
plt.xlabel('Date')
plt.ylabel('Money (INR)')
plt.title('Budget and Total Expenses by Date')
plt.xticks(rotation=45)  # Rotate x-axis labels for better readability
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()
