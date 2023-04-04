import {Matrix, Row, Fraction} from "./matrixFractions";

function CompareFloat(x, y, epsilon){
    if(Math.abs(x - y) < epsilon)
       return true; //they are same
       return false; //they are not same
 }

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

    test("inverting 10x10 matrix", () => {
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
        M.Print(true);
        let MInverted = M.LUInversion();
        MInverted.Print(true);
        let M_Inverted_Ans = [0.10025795585430151 , -0.5435622693226418 , -0.10009386958098374 , 0.17380273864430737 , 1.4684749296263968 , 2.7775875331369475 , -1.4584640753064706 , 1.791704641869694 , -0.003966276151435191 , -1.263185830467847,
            -0.06402547800024323 , 0.3367050876197583 , 0.05620163769503209 , -0.056621438628152436 , -0.9188270318869798 , -1.6159222761770256 , 0.8443659986761375 , -1.0614865213018867 , -0.002548606460047206 , 0.7535334149877175,
            -0.01827780226005967 , -0.33877067338001043 , 0.035257936046568975 , 0.15348483915824176 , 0.11797587615054408 , 1.3967684551639712 , -0.4699009922595088 , -0.16373148806886398 , 0.07809845700947322 , 0.17846480532505654,
            0.06424945118451697 , 0.7828216666542989 , -0.11613900322378852 , -0.35493829734757293 , -0.03133077409443156 , -4.348605143730334 , 1.7294950653212868 , -0.021775219479870492 , -0.14267788958865701 , -0.05693947930305134,
            0.11432580357016063 , 1.0037542340217454 , -0.07893576125176964 , -0.4347353702660289 , -1.3092871971976148 , -2.8892197114442384 , 0.954413381485344 , -1.21834929646311 , -0.17910913634144812 , 1.0807899480436698,
            -0.07250201042259662 , -0.014140651134392617 , -0.01468981198312847 , 0.031276196672184384 , -0.10342279238241826 , 0.549828542112086 , 0.03440659246469213 , 0.0492932463402651 , -0.015954526890873236 , 0.026191216675674173,
            -0.06479312305320958 , 0.3906960444984191 , 0.03844058269859246 , -0.14602640603064462 , -0.0687940483149333 , -1.6323553646519375 , 0.5561147956074197 , -0.5335914224251218 , -0.07372056377824347 , 0.29177518723681184,
            0.11999801830237819 , -0.5077843214629313 , 0.0312962535473648 , 0.16032816081438916 , 0.487596966859845 , 1.5094959155930645 , -0.5187679777564239 , 0.8179528716820766 , 0.08374387524103329 , -0.8195076407697989,
            0.00854393063742241 , 0.019764391352719058 , -0.0002352089909742671 , -0.010225551311584027 , -0.08659811301630674 , -0.14184883512200935 , 0.05859079671377178 , -0.026490605937445937 , 0.07398321353350042 , 0.012552863149555442,
            -0.01181644441100393 , -0.4340672064615672 , 0.056703561213528896 , 0.17853728789871248 , 0.1363861744780319 , 2.202260848032843 , -0.9613134477173721 , 0.3106408993348222 , 0.07213364632166433 , -0.038968108880582594];
        for (let i = 0; i < M.arr.length; i++) {
            expect(CompareFloat(M.arr[i].ToNumber(),M_Inverted_Ans[i], .0001));
        }
        
    });

});