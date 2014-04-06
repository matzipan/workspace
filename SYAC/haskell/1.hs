import Data.List
import Data.Maybe

d2n :: Char -> Int
d2n '0' = 0
d2n '1' = 1
d2n '2' = 2
d2n '3' = 3
d2n '4' = 4
d2n '5' = 5
d2n '6' = 6
d2n '7' = 7
d2n '8' = 8
d2n '9' = 9

s2n :: String -> Int
s2n = (foldl1 f).map d2n
	where f acc x = acc*10 + x  

whitespace :: Char -> Bool
whitespace x = elem x [' ', '\n', '\r', '\t'] 

dropLeadingWhitespace :: String -> String
dropLeadingWhitespace = dropWhile whitespace 

type V = String
type N = Int
data E = Var V | Val N | Plus E E | Mult E E 

instance Show E where
	show (Val x) = show x
	show (Var x) = x
	show (Plus x y) = "(" ++ show x ++ "+" ++ show y ++ ")"
	show (Mult x y) = "(" ++ show x ++ "*" ++ show y ++ ")"

simplify :: E -> E
simplify (x `Mult` (Val 1)) = simplify x
simplify ((Val 1) `Mult` x) = simplify x
simplify ((Val 0) `Plus` x) = simplify x
simplify (x `Plus` (Val 0)) = simplify x
simplify (x `Mult` y) = (simplify x) `Mult` (simplify y)
simplify (x `Plus` y) = (simplify x) `Plus` (simplify y)
simplify e = e

type Assoc a = [(String, a)]

testAssoc = [("x", 4), ("y", 2), ("z", 0)]


names :: Assoc a -> [String]
names = map fst

inAssoc::String -> Assoc a -> Bool
inAssoc s xs =  any (s==) $ names xs

fetch :: String -> Assoc a -> a
fetch s xs
	| (inAssoc s xs) && (isJust i) = snd $ last $ take ((fromJust i)+1) xs
	| otherwise = error "Not in associative" 
	where i = (elemIndex (s) (names xs))

update :: String -> a -> Assoc a -> Assoc a	
update s e xs = (s, e) : filter ((s /=).fst) xs

evaluate :: Assoc Int -> E -> Int
evaluate env (Val x) = x
evaluate env (Plus x y) = (evaluate env $ simplify x) + (evaluate env $ simplify y)
evaluate env (Mult x y) = (evaluate env $ simplify x) * (evaluate env $ simplify y)
evaluate env (Var v) = fetch v env



data Op = Add | Mul
data ET = Vr V | Vl N | Ap ET Op ET

evaluate2 :: Assoc Int -> ET -> Int
evaluate2 env (Vl x) = evaluate env (Val x)
evaluate2 env (Vr x) = evaluate env (Var x)
evaluate2 env (Ap x Add y) = evaluate env (Plus (Val (evaluate2 env x)) (Val (evaluate2 env y))) 
evaluate2 env (Ap x Mul y) = evaluate env (Mult (Val (evaluate2 env x)) (Val (evaluate2 env y)))


headT :: [a] -> Maybe a
headT [] = Nothing
headT xs = Just(head xs)

total :: (a->b) -> (a->Maybe b)
total f [] = Nothing
total f xs = Just $ f xs

tailT :: [a] -> Maybe a
tailT = total tail

lastT :: [a] -> Maybe a
lastT = total last