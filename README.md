# Game-Market
A turn-based C game where there exist 2 players: player A (you) and player B (Boss), and it works in the way that we have to attack the boss through option of investment along the way.
The boss can attack back with real-world economic events, and your goal is to reduce its HP to zero before yours runs out.

Two profession we can choose, such as trader or risk manager. The hp is larger for risk manager.
The option of investment including **ETF, Crypto, Bonds, Cash**, where each can either heal player A (you) or attack player B (Boss).

## This project demonstrate use of:
1. Enums
2. Structs
3. Seed random -> srand(), and randomness -> rand()
4. Loops, including infinite loop if user inputs wrong option
5. Game logic to deducting player A or B's hp, win/losses states

## Overview of the game
Choose the profession: 
1. Trader
2. Risk Manager

Player move
Choose the options of investment, for player this is crucial to win the market. Ensure we have larger hp than the boss to be able to attack.
The option to attack: 
1. ETF -> Quite stable damage 
4. Bonds -> Small heal to player A 
5. Crypto -> 80% possibility of fail and attack 0 damage, and 20% possibility of winning (produce 30-40 damage)
6. Cash -> Small heal to player A

After your turn, now it's the boss turn that will hit you with the market condition:
1. Inflation -> Quite small damage
2. Recession Smash -> Quite medium damage
3. Interest hike -> Can damage or undamage, according to panic level of customers towards market
4. Market crash 2008 -> Huge damage to attack us

-> If your hp reaches 0 first then you lose, but if the boss reaches 0 first then you win.

Lastly, worth to mention you can see the hp of player A and B every attack, heal or being attacked.

## Summary
The flow:
- Displays profession choice  
- Displays investment choices  
- Shows damage/healing each turn  
- Shows boss attacks  
- Shows updated HP after every action  
- Declares win or loss at the end
  
# Author: Silvi Claudia
