# CS360-lab-1
http://web.eecs.utk.edu/~plank/plank/classes/cs360/360/labs/lab1/index.html

## Installation
```
git clone https://github.com/bkayranci/CS360-lab-1.git --recurse-submodules
cd CS360-lab-1
make
```

## RUN
```
./parser fams/fam1
```

## RUN FLAGS
### -w
If you want to print screen (`stdout` and `stderr`), run with `-w` flag.

## TEST FILES
Test files are located in the fams directory.

## RUN TESTS
- run-fam1
- run-fam2
- run-fam3
- run-fam4
- run-fam5
- run-cyclefam
- run-redundant
- run-nonredundant

```
make run-fam1
```

If you want to print screen, you can do it following like,
```
make run-fam1 -e PROGRAM_FLAG=-w
```

## PROGRAM

### DEFINES
- TRUE 1
- FALSE 0

### STRUCTS

#### struct Person
This is used to keep the user information on the build screen.

#### struct Out
This is used to print to the struct screen.

### FUNCTIONS

#### insert_child

`PARAMETERS: insert_child(Person *p, Dllist children)`

`RETURN: void`

This is used to append to the Dllist.

#### print_tree
`PARAMETERS: print_tree(JRB people, Out *out)`

`RETURN: void`

This is used to print family tree.

#### is_cycle
`PARAMETERS: is_cycle(Person*P)`

`RETURN: int`

This is used to control cycle.

#### new_person
`PARAMETERS: *new_person(char *name, JRB people)`

`RETURN: *Person`

This is used to create new person.

#### get_name
`PARAMETERS: *get_name(IS is)`


`RETURN: *char`

This is used to get the person's full name.

#### has_flag
`PARAMETERS: has_flag (char *flag, int argc, char **argv)`

`RETURN: int`

This is used to control having flag of program.