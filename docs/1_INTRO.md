# 1. Introduction

Automated tests are structured in a heirarchical manner.  This enables a modular approach to unit testing.  There are three primary elements to the heirarchy: scenarios, sections, and runners.

## Scenario

A scenario is the lowest portion of the heirarchy.  A scenario represents exactly what it's named: some scenario your which code may be expected to deal with.  It is what makes calls to the test-subject's code and compares the result to an expected baseline.

## Section

All scenarios are grouped into sections.  Additionally, sections may be added to other sections.  Sections are what enable a modular approach to organizing tests.

## Runner

Runners are the highest portion of the heirarchy.  They are responsible for actually setting up and executing the tests, displaying the results.
