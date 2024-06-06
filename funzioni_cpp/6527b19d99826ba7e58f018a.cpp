void wake_up_new_task(struct task_struct *p, unsigned long clone_flags)
{
	unsigned long flags;
	struct rq *rq;

	rq = task_rq_lock(p, &flags);
	BUG_ON(p->state != TASK_RUNNING);
	update_rq_clock(rq);

	p->prio = effective_prio(p);

	if (!p->sched_class->task_new || !current->se.on_rq) {
		activate_task(rq, p, 0);
	} else {
		
		p->sched_class->task_new(rq, p);
		inc_nr_running(rq);
	}
	check_preempt_curr(rq, p);
#ifdef CONFIG_SMP
	if (p->sched_class->task_wake_up)
		p->sched_class->task_wake_up(rq, p);
#endif
	task_rq_unlock(rq, &flags);
}