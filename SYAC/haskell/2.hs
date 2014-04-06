import Data.Maybe

type RegExp a = [a] -> (Maybe [a], [a])

nil :: RegExp a

nil xs = (Just [], xs)

range :: (a->Bool) -> RegExp a
range f t@(x:xs)
	| f x == True = (Just [x], xs)
	| otherwise = (Nothing, t)

one :: Eq a => a -> RegExp a
one c = range (==c)

arb :: RegExp a
arb = range (const True)

alt :: Eq a => RegExp a -> RegExp a -> RegExp a