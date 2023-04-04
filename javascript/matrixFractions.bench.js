import { benchmarkSuite } from "jest-bench";
import {Matrix, Fraction} from "./matrixFractions";

  benchmarkSuite("Matrix using custom Fractions Class instead of Numbers", {
    // setup will not run just once, it will run for each loop
    setup() {

    },
  
    // same thing with teardown
    teardown() {
    },
  
    ["inverting 5x5 Matrix of Numbers "]: () => {
        let M = new Matrix(5,[
            5,7,9,4,4,
            2,4,7,1,4,
            7,9,3,1,2,
            5,6,3,6,2,
            1,4,2,5,2]);
        M.LUInversion();
    },

    ["inverting 5x5 Matrix of Fractions "]: () => {
        let M = new Matrix(5,[
            new Fraction(5),new Fraction(7),new Fraction(9),new Fraction(4),new Fraction(4),
            new Fraction(2),new Fraction(4),new Fraction(7),new Fraction(1),new Fraction(4),
            new Fraction(7),new Fraction(9),new Fraction(3),new Fraction(1),new Fraction(2),
            new Fraction(5),new Fraction(6),new Fraction(3),new Fraction(6),new Fraction(2),
            new Fraction(1),new Fraction(4),new Fraction(2),new Fraction(5),new Fraction(2)]);
        M.LUInversion();
    },

    ["inverting 10x10 Matrix of Fractions "]: () => {
        let M = new Matrix(10,[
            new Fraction(5),new Fraction(7),new Fraction(9),new Fraction(4),new Fraction(4), new Fraction(2),new Fraction(4),new Fraction(7),new Fraction(1),new Fraction(4),
            new Fraction(7),new Fraction(9),new Fraction(3),new Fraction(1),new Fraction(2),new Fraction(5),new Fraction(6),new Fraction(3),new Fraction(6),new Fraction(2),
            new Fraction(1),new Fraction(4),new Fraction(2),new Fraction(5),new Fraction(2),new Fraction(6),new Fraction(13),new Fraction(9),new Fraction(2),new Fraction(15),
            new Fraction(12),new Fraction(20),new Fraction(7,2),new Fraction(5,3),new Fraction(2,13),new Fraction(6,19),new Fraction(13,8),new Fraction(9,7),new Fraction(2,5),new Fraction(13,12),
            new Fraction(11,12),new Fraction(7,25),new Fraction(6,2),new Fraction(3,3),new Fraction(5,13),new Fraction(20,19),new Fraction(17,8),new Fraction(5,7),new Fraction(4,5),new Fraction(6,12),
            new Fraction(5,15),new Fraction(2,30),new Fraction(7,5),new Fraction(1,3),new Fraction(8,13),new Fraction(41,19),new Fraction(11,9),new Fraction(8,7),new Fraction(7,9),new Fraction(5,17),
            new Fraction(2,17),new Fraction(7,29),new Fraction(9,3),new Fraction(5,3),new Fraction(9,13),new Fraction(71,19),new Fraction(13,8),new Fraction(15,7),new Fraction(3,5),new Fraction(14,12),
            new Fraction(6,19),new Fraction(9,11),new Fraction(1,9),new Fraction(7,3),new Fraction(2,13),new Fraction(28,19),new Fraction(17,50),new Fraction(2,7),new Fraction(7,12),new Fraction(56,12),
            new Fraction(9,10),new Fraction(1,24),new Fraction(4,2),new Fraction(1,3),new Fraction(1,13),new Fraction(23,19),new Fraction(14,8),new Fraction(2,70),new Fraction(70,5),new Fraction(5,19),
            new Fraction(3,11),new Fraction(33,70),new Fraction(9,3),new Fraction(9,3),new Fraction(7,13),new Fraction(25,19),new Fraction(11,16),new Fraction(2,711),new Fraction(7,56),new Fraction(59,12)]);
        M.LUInversion();
    },


    
  });