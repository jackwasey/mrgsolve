# Copyright (C) 2013 - 2018  Metrum Research Group, LLC
#
# This file is part of mrgsolve.
#
# mrgsolve is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# mrgsolve is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with mrgsolve.  If not, see <http://www.gnu.org/licenses/>.

library(testthat)
library(mrgsolve)
library(dplyr)

Sys.setenv(R_TESTS="")

options("mrgsolve_mread_quiet"=TRUE)

context("test-as_data_set")


test_that("as_data_set basic", {
  e1 <- ev(amt = 100, ID = 1:2)
  e2 <- ev(amt = 200, ID = 1:3)
  data <- as_data_set(e1,e2)
  
  expect_equal(data$ID, c(1,2,3,4,5))
  expect_equal(data$amt, c(rep(100,2),rep(200,3)))
  
  data <- as_data_set(as.data.frame(e1),as.data.frame(e2))
  expect_equal(data$ID, c(1,2,3,4,5))
  expect_equal(data$amt, c(rep(100,2),rep(200,3)))
  
})



