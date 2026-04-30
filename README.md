# Battlefield Optimization System (C Project)

## Overview
This project simulates a battlefield grid and finds the best region with maximum score using efficient algorithms. It then extracts items from that region and applies the 0/1 Knapsack algorithm to maximize loot value based on player capacity.

---

## Features
- Generate battlefield grid (manual or random)
- Display grid values
- Find maximum sum submatrix (best region)
- Extract items based on grid values
- Apply 0/1 Knapsack for optimal loot selection

---

## Algorithms Used
- Kadane’s Algorithm (for 1D maximum subarray)
- Maximum Sum Submatrix (2D extension of Kadane’s Algorithm)
- 0/1 Knapsack (Dynamic Programming)

---

## Grid Value Mapping
| Value Range | Item Type |
|------------|----------|
| >= 15      | Guns     |
| >= 10      | Armor    |
| >= 5       | Medkit   |
| > 0        | Ammo     |

---

## Item Properties
| Item   | Value | Weight |
|--------|------|--------|
| Guns   | 60   | 40     |
| Ammo   | 40   | 20     |
| Medkit | 50   | 30     |
| Armor  | 50   | 40     |

---

## How It Works
1. User enters grid size
2. Choose:
   - Manual input
   - Random grid generation
3. Program displays the battlefield grid
4. Finds the best scoring region using maximum sum submatrix
5. Extracts items from that region
6. Applies 0/1 Knapsack with capacity = 120
7. Displays selected items and maximum loot value
---


