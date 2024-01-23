const float FIVE_PERCENT = .05;
const float TEN_PERCENT = .10;
const float FIFTEEN_PERCENT = .15;

double discount(double amount)
{
  float finalCost;

  if (amount < 50)
    finalCost = amount - (amount * FIVE_PERCENT);

  else if (amount >= 50 && amount < 100)
    finalCost = amount - (amount * TEN_PERCENT);
  
  else 
    finalCost = amount - (amount* FIFTEEN_PERCENT);

  return finalCost;
}
