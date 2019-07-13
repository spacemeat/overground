#include "jobManager.h"
#include <chrono>
#include <array>
#include <iostream>
#include <mutex>
#include <complex>

using namespace std;
using namespace std::chrono_literals;
using namespace overground;


class NopJob : public Job
{
protected:
  virtual void run_impl(JobManager * jobManager) override
  {
    auto c = complex { -1.0f, 0.0f };
    auto z = complex { 0.0f, 0.0f };
    for (int i = 0; i < 10000000; ++i)
    {
      z = z * z + c;
    }
  }
};

mutex mxConsole;
int jobsDone = 0;

void report(JobManager & jm)
{
  auto jobsDoneTotal = jm.getNumJobsDone();
  auto jobsDoneThisTime = jobsDoneTotal - jobsDone;
  jobsDone = jobsDoneTotal;

  lock_guard<mutex> lock(mxConsole);
  cout << "Running: " << (jm.isRunning() ? "true" : "false") << endl;
  cout << "Num workers: " << jm.getNumEmployedWorkers() << endl;
  cout << "Jobs enqueued: " << jm.getNumJobsEnqueued() << endl;
  cout << "Jobs started: " << jm.getNumJobsStarted() << endl;
  cout << "Jobs done: " << jobsDoneTotal << endl << " (this time: " << jobsDoneThisTime << ")" << endl;
}


int main(int argc, char ** argv)
{
  JobManager jm;
  jm.allocateWorkers(24);

  auto jobs = array<NopJob, 20000>();

  auto scheduler = thread([&]{
    int numJobsEnqueued = 0;
    for (auto & job : jobs)
    {
      jm.enqueueJob(& job);
      this_thread::sleep_for(1ms);
      numJobsEnqueued += 1;

      if (numJobsEnqueued % 1000 == 0)
      {
//        lock_guard<mutex> lock(mxConsole);
//        cout << "    ----- Jobs enqueued: " << numJobsEnqueued << endl;
      }
    }
  });

  {
    lock_guard<mutex> lock(mxConsole);
    cout << "Starting workers." << endl;
  }

  for (int i = 1; i < 24; ++i)
  {
    jm.setNumEmployedWorkers(i);
    this_thread::sleep_for(1s);
    report(jm);
  }

  scheduler.join();
  jm.stopAndJoin();

  return 0;
}