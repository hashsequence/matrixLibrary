import { benchmarkSuite } from "jest-bench";
import {Matrix, Row} from "./matrix";

  benchmarkSuite("Matrix", {
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
    
  });