import {Matrix, Row, Fraction} from "./matrixFractions";

describe("Matrix test", () => {
    test("test Fraction Class", () => {
        let f1 = new Fraction(3,5);
        let f2 = new Fraction(-2,8);
        expect(f1.Sum(f2).ToNumber()).toBe(.35);
        expect(f1.Difference(f2).ToNumber()).toBe(.85);
        expect(f1.Product(f2).ToNumber()).toBe(-6/40);
        expect(f1.Quotient(f2).ToNumber()).toBe(-24/10);
        expect(f1.Product(7)).toBe(undefined);
       
    });
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
        expect(M.LUInversion().GetArr()).toStrictEqual([2.25, 0.5, 0.375, 5/6, 1/3,1/12,4/3,1/3,1/3]);
    });

    test("inverting [5,	7,	9,	4,   4,2,	4,	7,	1,	4,7,	9,	3,	1,	2,5,	6,	3,	6,	2,1,	4,	2,	5,	2]", () => {
        let M = new Matrix(5,[5,	7,	9,	4,   4,2,	4,	7,	1,	4,7,	9,	3,	1,	2,5,	6,	3,	6,	2,1,	4,	2,	5,	2]);
        let [L,U] = M.LUDecomposition();
        expect(M.LUInversion().GetArr()).toStrictEqual([-43/181,	44/181,	-11/181,	94/181,	-85/181,
        42/181,	-107/362,	36/181,	-171/362,	145/362,
            80/181,	-109/362,	-9/181,	-93/362,	9/362,
            8/181,	-29/362,	-19/181,	45/362,	19/362,
            -325/362,	703/724,	-10/181,	457/724,	-161/724]);
    });

    test("Fraction(13,1) Mod Fraction(3,1)", () => {
        let f1 = new Fraction(13);
        let f2 = new Fraction(3)
        expect(f1.Mod(f2).ToNumber()).toBe(1);
    });

    test("Fraction(-13,1) Mod Fraction(3,1)", () => {
        let f1 = new Fraction(-13);
        let f2 = new Fraction(3)
        expect(f1.Mod(f2).ToNumber()).toBe(-1);
    });

    test("Fraction(13,1) Mod Fraction(-3,1)", () => {
        let f1 = new Fraction(13);
        let f2 = new Fraction(-3)
        expect(f1.Mod(f2).ToNumber()).toBe(1);
    });

    test("Fraction(-13,1) Mod Fraction(-3,1)", () => {
        let f1 = new Fraction(-13);
        let f2 = new Fraction(-3)
        expect(f1.Mod(f2).ToNumber()).toBe(-1);
    });

    test("Determinant test numbers", () => {
        let M = new Matrix(5,[
            5,7,9,4,4,
            2,4,7,1,4,
            7,9,3,1,2,
            5,6,3,6,2,
            1,4,2,5,2]);
        expect(M.Determinant().ToNumber()).toBe(724);
    });

    test("Determinant test Fractions", () => {
        let M = new Matrix(5,[
            new Fraction(5),new Fraction(7),new Fraction(9),new Fraction(4),new Fraction(4),
            new Fraction(2),new Fraction(4),new Fraction(7),new Fraction(1),new Fraction(4),
            new Fraction(7),new Fraction(9),new Fraction(3),new Fraction(1),new Fraction(2),
            new Fraction(5),new Fraction(6),new Fraction(3),new Fraction(6),new Fraction(2),
            new Fraction(1),new Fraction(4),new Fraction(2),new Fraction(5),new Fraction(2)]);
        expect(M.Determinant().ToNumber()).toBe(724);
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
});