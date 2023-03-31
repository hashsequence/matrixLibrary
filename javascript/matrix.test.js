import {Matrix, Row} from "./matrix";

describe("Matrix test", () => {
    test("decomping [2, -1, -2 ,-4, 6, 3 ,-4, -2, 8] ", () => {
            let M = new Matrix(3,[2, -1, -2 , -4, 6, 3 , -4, -2, 8]);
            let [L,U] = M.LUDecomposition();
            expect(L.arr).toStrictEqual([1, 0, 0, -2, 1, 0, -2, -1, 1]);
            expect(U.arr).toStrictEqual([2, -1, -2, 0, 4, -1, 0, 0, 3]);
        });

    test("multiplying two 4x4 matrices", () => {
        let A = new Matrix(4,[5, 7, 9, 10, 2, 3, 3, 8, 8, 10, 2, 3, 3, 3, 4, 8]);
        let B = new Matrix(4,[3, 10, 12, 18, 12, 1, 4, 9, 9, 10, 12, 2, 3, 12, 4, 10]);
        expect(A.Multiply(B).arr).toStrictEqual([210, 267, 236, 271, 93, 149, 104, 149, 171, 146, 172, 268, 105, 169, 128, 169]);
    });

    test("LUInversionerting [2, -1, -2 ,-4, 6, 3 ,-4, -2, 8] ", () => {
        let M = new Matrix(3,[2, -1, -2 , -4, 6, 3 , -4, -2, 8]);
        expect(M.LUInversion().arr).toStrictEqual([2.25, 0.5, 0.375, 0.8333333333333333, 1/3,1/12,4/3,1/3,1/3]);
    });

    test("Determinant test ", () => {
        let M = new Matrix(5,[
            5,7,9,4,4,
            2,4,7,1,4,
            7,9,3,1,2,
            5,6,3,6,2,
            1,4,2,5,2]);
        expect(M.Determinant()).toStrictEqual(724);
    });

    test("transpose test ", () => {
        let M = new Matrix(5,[
            5,7,9,4,4,
            2,4,7,1,4,
            7,9,3,1,2,
            5,6,3,6,2,
            1,4,2,5,2]);
        let M_T = new Matrix(5,[
            5,2,7,5,1,
            7,4,9,6,4,
            9,7,3,3,2,
            4,1,1,6,5,
            4,4,2,2,2]);
        expect(Matrix.Transpose(M).GetArr()).toStrictEqual(M_T.GetArr());
    });

    test("partial pivot matrix test ", () => {
        let M = new Matrix(3,[
            5,7,9,
            2,4,7,
            7,9,3]);
        let M_ans = new Matrix(3,[
            7,9,3,
            5,7,9,
            2,4,7,
           ]);
        let P_ans = new Matrix(3,[
        0,0,1,
        1,0,0,
        0,1,0
        ]);

        let [P,As] = Matrix.PartialPivot(M)
        expect(Matrix.Transpose(P).Multiply(As).GetArr()).toStrictEqual(M.GetArr());
        expect(As.GetArr()).toStrictEqual(M_ans.GetArr());
        expect(P.GetArr()).toStrictEqual(P_ans.GetArr());
    });

});