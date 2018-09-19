# TIE-50307 Real-time systems

## How to use SSH remotes

Using HTTPS remotes becomes quickly frustrating as it requires to input your credentials several times, even multiple times for a single `git` command.

Read [this document](https://course-gitlab.tut.fi/tie-50307-rt-systems-2018/course_upstream/snippets/20) for tips on how to securely use a semipermanent `git` profile with SSH keys for the shared VM environment of the course.

**Note**: If you choose to setup access through SSH keys, remember to use the SSH remote URL to clone your student repository and for the `course_upstream` remote.

## Quick guide to pull new exercise instructions

1. *(only-once)* `git remote add course_upstream https://course-gitlab.tut.fi/tie-50307-rt-systems-2018/course_upstream.git`
2. `git pull course_upstream`

**Note**: visit the [course_upstream project] to grab the SSH remote URL if you set up access with SSH keys.

## Quick guide to submit exercise assignment

1. `git commit` - remember to *add* new files
2. `git push`
3. Create tag for submission in GitLab - format `ExNN_submissionN`
4. `git push --tags`
5. Submit a link to the tag on the corresponding assignment in [Moodle][moodle]

## Git Help

If you need training to use Git, visit [Git Course in Plussa][git-plussa].


[moodle]: https://moodle2.tut.fi/course/view.php?id=11830
[git-plussa]: https://plus.cs.tut.fi/git/versio-1/
[course_upstream project]: https://course-gitlab.tut.fi/tie-50307-rt-systems-2018/course_upstream
