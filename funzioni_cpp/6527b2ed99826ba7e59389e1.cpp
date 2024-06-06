find_pipeline (pid, alive_only, jobp)
     pid_t pid;
     int alive_only;
     int *jobp;		
{
  int job;
  PROCESS *p;

  
  if (jobp)
    *jobp = NO_JOB;
  if (the_pipeline)
    {
      p = the_pipeline;
      do
	{
	  
	  if (p->pid == pid && ((alive_only == 0 && PRECYCLED(p) == 0) || PALIVE(p)))
	    return (p);

	  p = p->next;
	}
      while (p != the_pipeline);
    }
  
  if (last_procsub_child)
    {
      p = last_procsub_child;
      do
	{
	  
	  if (p->pid == pid && ((alive_only == 0 && PRECYCLED(p) == 0) || PALIVE(p)))
	    return (p);

	  p = p->next;
	}
      while (p != last_procsub_child);
    }

  job = find_job (pid, alive_only, &p);
  if (jobp)
    *jobp = job;
  return (job == NO_JOB) ? (PROCESS *)NULL : jobs[job]->pipe;
}