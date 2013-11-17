C++ ultra low-latency book, Fixed precision pricing
Joshua McKenzie
joshua.mckenzie@gmail.com

Similar to OrderBook, this is an ultra-low-latency order-based book.
This one uses a fixed precision pricing object rather than the *=100
truncation model the other book uses, so this should support some more
activity in the Foreign Exchange space for instance.

Performance numbers are actually comparable with the Order Book, so
there's really no reason to prefer that book over this.  I developed
the other initially and had this niggling annoyance of not having
implemented this, so I took a few hours a few days later and threw
this together.

NOTE: I've included FHErrorTracker.cpp in this project as well to work
around g++ being obnoxious about symbol exporting on the static
FHErrorTracker instance.  Clang builds and runs fine without it but
g++ likely needs some other kind of gymnastics to get it to load
the object that's been exported in the lib.  I'll leave that one
as an exercise to the reader at this point... ;)
