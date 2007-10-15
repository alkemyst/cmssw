#ifndef Candidate_CompositeRefCandidate_h
#define Candidate_CompositeRefCandidate_h
#include "DataFormats/Candidate/interface/Candidate.h"
/** \class reco::CompositeRefCandidate
 *
 * a reco::Candidate composed of daughters. 
 * The daughters has persistent references (edm::Ref <...>) 
 * to reco::Candidate stored in a separate collection.
 *
 * \author Luca Lista, INFN
 *
 * \version $Id: CompositeRefCandidate.h,v 1.18 2007/10/15 11:51:25 llista Exp $
 *
 */

#include "DataFormats/Candidate/interface/iterator_imp_specific.h"

namespace reco {

  class CompositeRefCandidate : public Candidate {
  public:
    /// collection of references to daughters
    typedef CandidateRefVector daughters;
    /// collection of references to daughters
    typedef CandidateRefVector mothers;
    /// default constructor
    CompositeRefCandidate() : Candidate() { }
    /// constructor from values
    CompositeRefCandidate( Charge q, const LorentzVector & p4, const Point & vtx = Point( 0, 0, 0 ),
			   int pdgId = 0, int status = 0, bool integerCharge = true ) :
      Candidate( q, p4, vtx, pdgId, status, integerCharge ) { }
    /// constructor from values
    CompositeRefCandidate( Charge q, const PolarLorentzVector & p4, const Point & vtx = Point( 0, 0, 0 ),
			   int pdgId = 0, int status = 0, bool integerCharge = true ) :
      Candidate( q, p4, vtx, pdgId, status, integerCharge ) { }
    /// constructor from a particle
    CompositeRefCandidate( const Particle & p ) : Candidate( p ) { }
    /// destructor
    virtual ~CompositeRefCandidate();
    /// returns a clone of the candidate
    virtual CompositeRefCandidate * clone() const;
    /// first daughter const_iterator
    virtual const_iterator begin() const;
    /// last daughter const_iterator
    virtual const_iterator end() const;
    /// first daughter iterator
    virtual iterator begin();
    /// last daughter iterator
    virtual iterator end();
    /// number of daughters
    virtual size_t numberOfDaughters() const;
    /// return daughter at a given position, i = 0, ... numberOfDaughters() - 1 (read only mode)
    virtual const Candidate * daughter( size_type ) const;
    /// return daughter at a given position, i = 0, ... numberOfDaughters() - 1
    virtual Candidate * daughter( size_type );
    /// add a daughter via a reference
    void addDaughter( const CandidateRef & );    
    /// add a daughter via a reference
    void addMother( const CandidateRef & );    
    /// clear daughter references
    void clearDaughters() { dau.clear(); }
    /// reference to daughter at given position
    CandidateRef daughterRef( size_type i ) const { return dau[ i ]; }
    /// references to daughtes
    const daughters & daughterRefVector() const { return dau; }
    /// set daughters product ID
    void resetDaughters( const edm::ProductID & id ) { dau = daughters( id ); }
    /// number of mothers (zero or one in most of but not all the cases)
    virtual size_t numberOfMothers() const;
    /// return pointer to mother
    virtual const Candidate * mother( unsigned int i = 0 ) const;

  private:
    /// const iterator implementation
    typedef candidate::const_iterator_imp_specific<daughters> const_iterator_imp_specific;
    /// iterator implementation
    typedef candidate::iterator_imp_specific_dummy<daughters> iterator_imp_specific;
    /// collection of references to daughters
    daughters dau;
    /// collection of references to mothers
    daughters mom;
    /// check overlap with another candidate
    virtual bool overlap( const Candidate & ) const;
  };

  inline void CompositeRefCandidate::addDaughter( const CandidateRef & cand ) { 
    dau.push_back( cand ); 
  }

  inline void CompositeRefCandidate::addMother( const CandidateRef & cand ) { 
    mom.push_back( cand ); 
  }
}

#endif
