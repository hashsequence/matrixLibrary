import { benchmarkSuite } from "jest-bench";
import {Matrix, Row} from "./matrix";

benchmarkSuite("Matrix", {
    // setup will not run just once, it will run for each loop
    setup() {

    },
  
    // same thing with teardown
    teardown() {
    },
  
    ["inverting [2, -1, -2 ,-4, 6, 3 ,-4, -2, 8] "]: () => {
        let M = new Matrix(3,[2, -1, -2 , -4, 6, 3 , -4, -2, 8]);
        M.Inversion();
    },
  });