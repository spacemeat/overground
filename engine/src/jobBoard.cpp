#include "jobBoard.h"
#include "job.h"

using namespace std;
using namespace overground;


JobBoard::JobBoard(string_view name)
: name(name)
{

}


void JobBoard::clear()
{
  recurringJobs.clear();
  decltype(oneTimeJobs) swappy;
  oneTimeJobs.swap(swappy);
}


void JobBoard::postJob(Job * job, bool recurring)
{
  static unsigned int jobPostingId = 1;
  unsigned int thisJobPostingId = jobPostingId ++;
  if (recurring)
    { recurringJobs.emplace_back(thisJobPostingId, job); }
  else
    { oneTimeJobs.push({thisJobPostingId, job}); }
  
  job->setPosted();
}

