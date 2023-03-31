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
    
  });