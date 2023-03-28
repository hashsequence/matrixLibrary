import {Matrix, Row} from "./matrixFractions";

describe("Matrix test", () => {
    test("decomping [2, -1, -2 ,-4, 6, 3 ,-4, -2, 8] ", () => {
            let M = new Matrix(3,[2, -1, -2 , -4, 6, 3 , -4, -2, 8]);
            let [L,U] = M.LUDecomposition();
            expect(L.GetArr()).toStrictEqual([1, 0, 0, -2, 1, 0, -2, -1, 1]);
            expect(U.GetArr()).toStrictEqual([2, -1, -2, 0, 4, -1, 0, 0, 3]);
        });

    test("multiplying two 4x4 matrices", () => {
        let A = new Matrix(4,[5, 7, 9, 10, 2, 3, 3, 8, 8, 10, 2, 3, 3, 3, 4, 8]);
        let B = new Matrix(4,[3, 10, 12, 18, 12, 1, 4, 9, 9, 10, 12, 2, 3, 12, 4, 10]);
        expect(A.Multiply(B).GetArr()).toStrictEqual([210, 267, 236, 271, 93, 149, 104, 149, 171, 146, 172, 268, 105, 169, 128, 169]);
    });

    test("inverting [2, -1, -2 ,-4, 6, 3 ,-4, -2, 8] ", () => {
        let M = new Matrix(3,[2, -1, -2 , -4, 6, 3 , -4, -2, 8]);
        expect(M.Inversion().GetArr()).toStrictEqual([2.25, 0.5, 0.375, 5/6, 1/3,1/12,4/3,1/3,1/3]);
    });

});