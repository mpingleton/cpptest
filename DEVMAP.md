# CPPTEST Development Map and Checklist

## Current Priority Tasks

- [ ] Develop Assertion() and Case() classes.
- [ ] Develop Suite() class.
- [ ] Develop Runner() class.
 
## Milestones

- [ ] Alpha
- [ ] Beta (Closed Testing)
- [ ] Beta (Open Testing)
- [ ] Stable

## Features

### Current

(Nothing to show currently)

### Future

(Nothing to show currently)

## Current Problems

(Nothing to show currently)

## Component Tasks

- [ ] Assertion() class
  - [ ] Prototype definition
  - [ ] Constructor/Destructor
  - [ ] Methods 
    - [ ] isComplete() and isPassing()
    - [ ] toString()

- [ ] Case() class
  - [ ] Prototype definition
  - [ ] Constructor/Destructor
  - [ ] Methods
    - [ ] expect()
    - [ ] expectToEqual() (overrides for comparing integers, floats, and strings)
    - [ ] skip(), isPassing()
    - [ ] numberTotalAssertions() and numberFailingAssertions()
    - [ ] toString()

- [ ] Suite() class
  - [ ] Prototype definition
  - [ ] Constructor/Destructor
  - [ ] Methods
    - [ ] toString() method

- [ ] Runner() class
  - [ ] Prototype definition
  - [ ] Constructor/Destructor
  - [ ] Methods
    - [ ] run()
    - [ ] numberTotalSuites()
    - [ ] toString()