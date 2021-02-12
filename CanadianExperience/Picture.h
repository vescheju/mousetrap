/**
 * \file Picture.h
 *
 * \author Charles B. Owen
 *
 * The picture we are drawing
 */

#pragma once

#include <vector>
#include "PictureObserver.h"
#include "Timeline.h"
#include "Adapter.h"

class CActor;
class CMachineDrawable;

/**
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of 
 * our actors, which then contains the drawables. 
 */
class CPicture
{
public:
    CPicture();
    virtual ~CPicture();

    /// Copy Constructor (Disabled)
    CPicture(const CPicture &) = delete;
    /// Assignment Operator (Disabled)
    /// \return nothing
    CPicture &operator=(const CPicture &) = delete;

    /** The picture size
    * \returns Size */
    Gdiplus::Size GetSize() { return mSize; }

    /** The picture size
    * \param size The new picture size */
    void SetSize(Gdiplus::Size size) { mSize = size; }

    void AddObserver(CPictureObserver *observer);
    void RemoveObserver(CPictureObserver *observer);
    void UpdateObservers();
    void Draw(Gdiplus::Graphics *graphics);
    void AddActor(std::shared_ptr<CActor> actor);

    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);

    /**
    * Get the first machine
    * \returns a shared pointer to the first machine
    */
    std::shared_ptr<CAdapter> GetMachine1() { return mMachine1; }

    /**
    * Get the second machine
    * \returns a shared pointer to the second machine
    */
    std::shared_ptr<CAdapter> GetMachine2() { return mMachine2; }

    /** Iterator that iterates over the actors in a picture */
    class ActorIter
    {
    public:
        /** Constructor
        * \param picture Picture we are iterating
        * \param pos Starting position */
        ActorIter(CPicture *picture, int pos) : mPicture(picture), mPos(pos) {}

        /** Test for end of the iterator
        * \param other Other object to test against
        * \returns True if we this position equals not equal to the other position */
        bool operator!=(const ActorIter &other) const
        {
            return mPos != other.mPos;
        }

        /** Get value at current position
        * \returns Value at mPos in the collection */
        std::shared_ptr<CActor> operator *() const { return mPicture->mActors[mPos]; }

        /** Increment the iterator
        * \returns Reference to this iterator */
        const ActorIter& operator++()
        {
            mPos++;
            return *this;
        }


    private:
        CPicture *mPicture; ///< Picture we are iterating over
        int mPos;           ///< Position in the collection
    };

    /** Get an iterator for the beginning of the collection
    * \returns Iter object at position 0 */
    ActorIter begin() { return ActorIter(this, 0); }

    /** Get an iterator for the end of the collection
    * \returns Iter object at position past the end */
    ActorIter end() { return ActorIter(this, mActors.size()); }

    /** Get a pointer to the Timeline object
    * \returns Pointer to the Timeline object
    */
    CTimeline *GetTimeline() { return &mTimeline; }
    void SetAnimationTime(double time);
    double GetAnimationTime();

    /** Set machine 1 pointer
    * \param machine set the machine1
    */
    void SetMachine1(std::shared_ptr<CAdapter> machine) { mMachine1 = machine; }
    
    /** Set machine 2 pointer
    * \param machine set the machine2
    */
    void SetMachine2(std::shared_ptr<CAdapter> machine) { mMachine2 = machine; }
private:
    /// The picture size
    Gdiplus::Size mSize = Gdiplus::Size(800, 600);

    /// The observers of this picture
    std::vector<CPictureObserver *> mObservers;

    //! The actors associated with this picture
    std::vector<std::shared_ptr<CActor>> mActors;

    /// The animation timeline
    CTimeline mTimeline;
    /// Represents our first machine
    std::shared_ptr<CAdapter> mMachine1;
    /// Represents our second machine
    std::shared_ptr<CAdapter> mMachine2;

};

