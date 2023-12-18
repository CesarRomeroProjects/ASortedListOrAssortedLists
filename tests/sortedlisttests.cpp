#include "catch_amalgamated.hpp"

#include <string>
#include "SortedList.hpp"


namespace{

TEST_CASE("PreliminaryTests", "[RequiredOne]")
{
    SortedList<unsigned, std::string> l;
    l.insert(1, "One");
    l.insert(2, "Two");
    l.insert(3, "Three");
    REQUIRE(l.contains(1));
    REQUIRE(l.contains(2));
    REQUIRE(l.contains(3));
    REQUIRE(! l.contains(4) );
    REQUIRE(! l.contains(0) );
    REQUIRE(l.size() == 3);
    REQUIRE(! l.isEmpty() );
}

TEST_CASE("ReverseInserts", "[RequiredOne]")
{
    SortedList<unsigned, std::string> l;
    l.insert(3, "Three");
    l.insert(2, "Two");
    l.insert(1, "One");
    REQUIRE(l.contains(1));
    REQUIRE(l.contains(2));
    REQUIRE(l.contains(3));
    REQUIRE(! l.contains(4) );
    REQUIRE(! l.contains(0) );
}

TEST_CASE("MyFirstRemovals1", "[RequiredOne]")
{
    SortedList<unsigned, std::string> l;
    l.insert(1, "One");
    l.insert(2, "Two");
    l.insert(3, "Three");
    l.remove(1);
    REQUIRE(! l.contains(1));
    REQUIRE(l.contains(2));
    REQUIRE(l.contains(3));
    REQUIRE(! l.contains(4) );
}

TEST_CASE("MyFirstRemovals2", "[Explanatory]")
{
    SortedList<unsigned, std::string> l;
    l.insert(1, "One");
    l.insert(2, "Two");
    l.insert(3, "Three");
    l.remove(2);
    REQUIRE(l.contains(1));
    REQUIRE(! l.contains(2));
    REQUIRE(l.contains(3));
    REQUIRE(! l.contains(4) );
}

TEST_CASE("MyFirstRemovals3", "[Explanatory]")
{
    SortedList<unsigned, std::string> l;
    l.insert(1, "One");
    l.insert(2, "Two");
    l.insert(3, "Three");
    l.remove(3);
    REQUIRE(l.contains(1));
    REQUIRE(l.contains(2));
    REQUIRE(! l.contains(3));
    REQUIRE(! l.contains(4) );
}

TEST_CASE("ContainsWithCarmichaelNumbers", "[Explanatory]")
{
    // because Carmichael numbers are fun
    SortedList<unsigned, std::string> cms;
    cms.insert(561, "First");
    cms.insert(1105, "Second");
    cms.insert(1729, "Third");
    cms.insert(2465, "Fourth");
    REQUIRE(cms.getIndex(561) == 0);
    REQUIRE(cms.getIndex(1105) == 1);
    REQUIRE(cms.getIndex(1729) == 2);
    REQUIRE(cms.getIndex(2465) == 3);
    REQUIRE_THROWS_AS( cms.getIndex(600), KeyNotFoundException );
    REQUIRE_THROWS_AS( cms.getIndex(6000), KeyNotFoundException );
}

TEST_CASE("LargestLessThanTest1", "[RequiredTwo]")
{
    SortedList<unsigned, std::string> cms;
    cms.insert(561, "First");
    cms.insert(1105, "Second");
    cms.insert(1729, "Third");
    cms.insert(2465, "Fourth");
    REQUIRE_THROWS_AS( cms.largestLessThan(560), KeyNotFoundException );
    REQUIRE_THROWS_AS( cms.largestLessThan(561), KeyNotFoundException );

    REQUIRE( cms.largestLessThan(1104) == 561  );
    REQUIRE( cms.largestLessThan(1728) == 1105 );
    REQUIRE( cms.largestLessThan(1900) == 1729 );
    REQUIRE( cms.largestLessThan(2470) == 2465 );
    REQUIRE( cms.largestLessThan(4096) == 2465 );

}

// Note that this is not "required" in the sense of getting this section graded.
// However, I strongly suggest you get this case working.  Just because it isn't
// in the "required" category doesn't mean I won't be grading things like this.
// (Or maybe I'll even have this as a grading test, who knows?)
TEST_CASE("SmallestGreaterThanTest1", "[Explanatory]")
{
    SortedList<unsigned, std::string> cms;
    cms.insert(561, "First");
    cms.insert(1105, "Second");
    cms.insert(1729, "Third");
    cms.insert(2465, "Fourth");

    REQUIRE_THROWS_AS( cms.smallestGreaterThan(2470), KeyNotFoundException );
    REQUIRE_THROWS_AS( cms.smallestGreaterThan(4096), KeyNotFoundException );

    REQUIRE( cms.smallestGreaterThan(560) == 561  );
    REQUIRE( cms.smallestGreaterThan(1) == 561  );
    REQUIRE( cms.smallestGreaterThan(562) == 1105 );
    REQUIRE( cms.smallestGreaterThan(1728) == 1729 );
    REQUIRE( cms.smallestGreaterThan(2048) == 2465 );

}

TEST_CASE("EveryonesCopyAndAssignmentOperatorCanBeGraded", "[RequiredThree]")
{
    /*
        Our grading script requires that every segment have
        at least one "required" test case.  

        This test case will pass for *everyone* 

        Be sure to test your copy constructor and assignment operator!

        Our grading test cases will be more thorough than this one.
    */
    REQUIRE(true);
}


TEST_CASE("SubscriptOperatorAsAccessor", "[RequiredFour]")
{
    SortedList<unsigned, std::string> cms;
    cms.insert(561, "First");
    cms.insert(1105, "Secnod");
    cms.insert(1729, "Thrid");
    cms.insert(2465, "Fourth");
    REQUIRE(cms[561] == "First");
    REQUIRE(cms[1105] == "Secnod");
    REQUIRE(cms[1729] == "Thrid");
    REQUIRE(cms[2465] == "Fourth");
    REQUIRE_THROWS_AS( cms[600], KeyNotFoundException );
    REQUIRE_THROWS_AS( cms[6000], KeyNotFoundException );
}

TEST_CASE("SubscriptOperatorReturnsReference", "[RequiredFour]")
{
    SortedList<unsigned, std::string> cms;
    cms.insert(561, "First");
    cms.insert(1105, "Secnod");
    cms.insert(1729, "Thrid");
    cms.insert(2465, "Fourth");
    // oops, let's fix those typos.
    cms[1105] = "Second";
    cms[1729] = "Third";
    REQUIRE(cms[561] == "First");
    REQUIRE(cms[1105] == "Second");
    REQUIRE(cms[1729] == "Third");
    REQUIRE(cms[2465] == "Fourth");
}

// don't forget to test the const version too.  See your notes for how to do this!
TEST_CASE("SubscriptOperatorConstTest", "[FYI]")
{
    SortedList<unsigned, int> cms;
    cms.insert(25, 5);
    cms.insert(50, 10);
    cms.insert(75, 15);
    cms.insert(100, 20);

    const SortedList<unsigned, int> & constSortedList{cms};
    
    REQUIRE(constSortedList[25] == 5);
    REQUIRE(constSortedList[50] == 10);
    REQUIRE(constSortedList[75] == 15);
}

/*
    Note that none of the "required" test cases in part four
    use the ++ or == operators.  We will still be grading these, 
    for obvious reasons.
*/
TEST_CASE("SimpleTestsOfEquality", "[Explanatory]")
{
    SortedList<unsigned, std::string> l1;
    SortedList<unsigned, std::string> l2;
    REQUIRE(l1 == l2);
    l1.insert(561, "First");
    REQUIRE(!(l1 == l2));  
    l2.insert(561, "First");
    REQUIRE(l1==l2);
}

TEST_CASE("Testing++Operator", "[Explanatory]")
{
    SortedList<std::string, unsigned> numbers;
    numbers.insert("Jenny", 8675309);
    ++numbers;
    REQUIRE(numbers["Jenny"] == 8675310); // that hurt to type.
}

TEST_CASE("InsertingStringsTest", "[FYI]")
{
    SortedList<unsigned, std::string> alphabet;
    alphabet.insert(26, "Z");
    alphabet.insert(25, "Y");

    REQUIRE(alphabet.largestLessThan(35) == 26);
    REQUIRE(alphabet.smallestGreaterThan(10) == 25);
}

TEST_CASE("CopyConstructorTestOne", "[FYI]") 
{
    SortedList<std::string, int> objOne;
    SortedList<std::string, int> objTwo = objOne;

    objOne.insert("A", 1);
    objOne.insert("B", 2);

    REQUIRE(objOne.size() == 2);
    REQUIRE(objTwo.size() == 0);
}

TEST_CASE("CopyConstructorTestTwo", "[FYI]")
{
    SortedList<unsigned, std::string> objOne;
    objOne.insert(5, "Wendys");

    SortedList<unsigned, std::string> objTwo = objOne;

    REQUIRE(!objOne.insert(5, "Subway")); // TESTS WHEN KEY IS PRESENT, RETURNS FALSE.
    REQUIRE(objOne.size() == 1);
    REQUIRE(objTwo.size() == 1);

    objOne.insert(6, "Subway");
    REQUIRE(!(objOne == objTwo));
}

TEST_CASE("ConstTest", "[FYI]")
{
    SortedList<unsigned, std::string> cms;
    cms.insert(2000, "Hello");

    const SortedList<unsigned, std::string> constCMS = cms;
    cms[2000] = "World";
    REQUIRE(constCMS[2000] == "Hello");
    REQUIRE(cms[2000] == "World");
}

TEST_CASE("SortTest", "[FYI]")
{
    SortedList<std::string, double> cms;
    cms.insert("Hello", 25.5);
    cms.insert("World", 40.3);
    cms.insert(",", 50.7);
    cms.insert("I", 70.6);
    cms.insert("am", 20.4);
    cms.insert("Cesar", 10.3);

    REQUIRE(cms.getIndex("Hello") == 2);
    REQUIRE(cms.getIndex("World") == 4);
}

} // end namespace

