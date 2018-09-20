# TIE-50307 Real-time systems

--------------------------------------------------------------------------------
## Important Notice

This project uses a Git extension for versioning large binary files called [Git Large File Storage][git-lfs].

Every clone of this repository **MUST** initialize the Git LFS extension. Immediately after a clone operation, inside the repository, the following command **MUST** be issued:

~~~bash
git lfs install
~~~

The above command will setup the correct *hooks* in the <u>local copy</u> of the repository: these *hooks* will automate the use of the LFS extension, so that, transparently, using the usual workflow of `git add`/`git commit`/`git push`, a selection of the files will be stored differently.

The course VM already includes all the required dependencies to use this extension.

--------------------------------------------------------------------------------


## How to use SSH remotes

Using HTTPS remotes becomes quickly frustrating as it requires to input your credentials several times, even multiple times for a single `git` command.

Read [this document](https://course-gitlab.tuni.fi/tie-50307-real-time-systems_2019-2020/course_upstream/snippets/1) for tips on how to securely use a semipermanent `git` profile with SSH keys for the shared VM environment of the course.

**Note**: If you choose to setup access through SSH keys, remember to use the SSH remote URL to clone your student repository and for the `course_upstream` remote.

## Quick guide to pull new exercise instructions

1. *(only-once)* `git remote add course_upstream https://course-gitlab.tuni.fi/tie-50307-real-time-systems_2019-2020/course_upstream.git`
2. `git pull course_upstream master`

**Note**: visit the [course_upstream project] to grab the SSH remote URL if you set up access with SSH keys.

## Quick guide to submit exercise assignment

1. `git commit` - remember to *add* new files
2. `git push`
3. Create tag for submission in GitLab - format `ExNN_submissionN`
4. `git push --tags`
5. Submit a link to the tag on the corresponding assignment in [Moodle][moodle]

## Git Help

If you need training to use Git, visit [Git Course in Plussa][git-plussa].


[moodle]: https://moodle.tuni.fi/course/view.php?id=2227
[git-plussa]: https://plus.cs.tut.fi/git/versio-2/
[course_upstream project]: https://course-gitlab.tuni.fi/tie-50307-real-time-systems_2019-2020/course_upstream
[git-lfs]: https://git-lfs.github.com/
