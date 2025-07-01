
# Task: Develop a system for a company that sells auto parts


## Overview
- **Auto parts are sold via a catalog and mail order.**
- **The system will handle:**
  - Credit card payment.
  - Assistance with packing and shipping of orders.
  - Keeping inventory.

## Customers Interface (1)
- Customers will be allowed to place and pay for orders online.
- Customers will be presented with a custom ordering program that allows them to select products from a catalog.
- Customers can order products with differing quantities.

## Product Details for Customer
Products have:
- Name
- Description
- Picture
- Price
- Available quantity

### Warehouse Interfaces (2)

## Packing Interface:
- Worker should be able to print packing lists for completed orders
- Worker should be able to retrieve items from the warehouse, and package them up.
- Worker should be able to add an invoice and shipping label (both printed with the new system).


- successful packing and shipping completes the order and is recordered in the order status.
    an email is sent to the customer confirming that the order is shipped.

## Interface for Receiving Desk
- An interface at the receiving desk for updating inventory.

- Whenever products are delivered they are added to the inventory.
- They can be recognized by their description or part number.
- Their quantity on hand should also be updated.
- Note: the legacy product database does not contain inventory information.

### Administrative Interface (1)
- allows to set the shipping and handling charges
- Allows the user to view all orders.

- shipping and handling charges are based on the weight of a complete order. 
- This interface allows to set the weight brackets and their charges.
- Orders can be searched based on data range, status (authorized, shipped) or price range.
- The complete order detail is displayed for a selected order.


## System Requirements ()
### Completing Customer Orders
- **Once the customer chooses to order a product(s), the system should:**
- Compute the total price.
- Add shipping and handling charge.
- Get the customer's name, email, mailing address, and credit card information.
- Authorize the credit card.

### After Finalizing Orders
- Process steps for packing and shipping.
- Send a confirmation email to the customer.

## System details
### Legacy product database 
-**Setup interfacing with this db (ege details provided later).
- **Product Attributes.**
- part number
- description
- weight
- picture link
- price
## new database:
- Quantity on hand for each product.
- Customer orders.
## Credit Card processing system
- **authorization requires:**
- Credit card number
- expiration date
- purchase amount.
- **The processing system confirms with an authorization number (ege details provided later).


