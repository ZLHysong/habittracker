# Habit Tracker

## SYNOPSIS

`habittracker [OPTION] [HABIT]`

## DESCRIPTION

Habit Tracker is a simple meant to help you track your daily tasks in a way that is simple and easy to use. 
The basic concept is that you will have a list of things you do every day, meditate, study, exercise, hydrate, etc. This application will put those into a simple, pretty calendar so you can see with one line whether you met your goals for each day this month.

## TODO

- Delete a Habit
- Uncomplete a Habit
- Show all Calendars from one command

## OPTIONS

- `-a` <habitname>, `--add`
  - Adds a new habit
- `-c` <habitname>, `--complete`
  - Marks a habit complete for today
- `-d` <habitname>, `--d` (THIS FEATURE IS NOT CURRENTLY FUNCTIONAL)
  - Deletes a habit
- `-l` <habitname>, `--list`
  - Draws a calendar for the given habit
- `-g` <habitname>, `--gethabits`
  - Lists all habits
- `-u` <habitname>, `--uncomplete` (THIS FEATURE IS NOT CURRENTLY FUNCTIONAL)
  - Marks a habit uncomplete for today

## LEGEND

- `◆` Task Completed
- `◇` Task Not Completed
- `∙` Day Not Happened Yet

## AUTHOR

Zachery Hysong

## NOTES

This is a project that was made (so far) in one day, about 15 hours worth of work, and is my first real C++ project outside
the simple 'hello world' applications. As such, it is far from optimized, has many quirks, lots of potential bugs, etc.
The plan is that I will be adding more to this over time, refactoring the code, optimizing it, and adding features over time.

My reason for making this application was two-fold. First, I wanted a C++ program that I wrote more or less myself to put in
my portfolio, and second, I wanted an app that I would actually use myself on a regular basis. This is not intended to solve
any real world problems that I see other people having, but is more just a personal project that I want to share.
That said, see the next section if you are interested in discussing it further.

## REPORTING BUGS AND MAKING SUGGESTIONS

Feel free to email me with any bugs or suggestions at `zlhysong@gmail.com`

## COPYRIGHT

Copyright © 2020 Zachery Hysong. License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent permitted by law.