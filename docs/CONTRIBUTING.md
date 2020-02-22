# Contributing to Snake

:snake: First off, welcome and thank you for considering to contribute :snake:

The following is a set of guidelines for contributing to Snake, which is hosted in [CrustaShrimp/Snake](https://github.com/CrustaShrimp/Snake) on GitHub. 
For contributing to succeed, there are some guidelines (flexible, not hard rules). Use common sense and feel free to propose changes to this document as well in a PR.

#### Table Of Contents

[Code of Conduct](#code-of-conduct)

[TL;DR](#TLDR)

[Before getting started](#what-should-i-know-before-i-get-started)
  * [Snake, the basics](#snake-the-basics)
  * [Snake, the extra's](#snake-the-extras)

[How Can I Contribute?](#how-can-i-contribute)
  * [Reporting Bugs](#reporting-bugs)
  * [Suggesting Features](#suggesting-features)
  * [Your First Code Contribution](#your-first-code-contribution)
  * [Pull Requests](#pull-requests)

[Styleguides](#styleguides)
  * [Git Commit Messages](#git-commit-messages)

[Additional Notes](#additional-notes)
  * [Issue and Pull Request Labels](#issue-and-pull-request-labels)

## Code of Conduct

This project and everyone participating in it is governed by the [Snake Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to uphold this code.

## TL;DR

**Note:** Feel free to ask questions as an [issue](https://github.com/CrustaShrimp/Snake/issues) (there is even a template), report bugs or send feature requests. Pull requests are also often checked, but they should be linked to an [issue](https://github.com/CrustaShrimp/Snake/issues).

### Contribute by:
- Downloading the latest release and playing it.
- Making Pull Requests to change the codebase. 

## What should I know before I get started?

### Snake, the basics
The concept of snake is quite old, stemming from the Nokia age.
In principle, the game is quite easy: 
- You control the direction of a moving snake. 
- Food is provided at random places.
- Eating food makes the snake grow one piece instantaniously.
- Touching a part of the snake is game over
- A score is kept, more food eaten is more score.

### Snake, the extra's
Apart from the basics, some extra features can be added:
- A background sound can be played
- Difficulty settings can be incorporated, where the difficulty is expressed by speed of the snake.
- A highscore page can be displayed
- A help page with all controls can be included
- The eaten food can make the snake swollen until the tail of the snake reaches the old food location
- Temporary bonus food can be planted for a certain time

### Design Decisions

When we make a significant decision in how we maintain the project and what we can or cannot support, we will document it in the [DesignChoices](DesignChoices.md). If you have a question around how we do things, check to see if it is documented there. If it is *not* documented there, please open a new question on [issues](https://github.com/CrustaShrimp/Snake/issues)

## How Can I Contribute?

There are a couple of different ways to contribute to Snake:
- **Downloading the latest release and playing it.** 
By playing Snake, you can not only have fun and try to beat the highscore, but also encounter bugs or annoyances.
If you do, please feel free to submit a bugreport or feature request here [issues](https://github.com/CrustaShrimp/Snake/issues), so the game can be improved. Basically, every player is also a beta-tester!
- **Making Pull Requests to change the codebase.** 
This is the more traditional view on contributing, although [issues](https://github.com/CrustaShrimp/Snake/issues) can only be solved bugs and feature requests are found and reported!

### Reporting Bugs

This section guides you through submitting a bug report for Snake. Following these guidelines helps everyone understand your report , reproduce the bug and find related reports or ultimately fix the bug!

Before creating bug reports, please check [this list](#before-submitting-a-bug-report) as you might find out that you don't need to create one. When you are creating a bug report, please [include as many details as possible](#how-do-i-submit-a-good-bug-report). Fill out the bug form on [issues](https://github.com/CrustaShrimp/Snake/issues), the information it asks for helps us resolve issues faster.

> **Note:** If you encounter a **Closed** issue that seems simmilar to what you are experiencing, open a **new** issue and include a link to the original issue in the body of your new one.

#### Before Submitting A Bug Report

* **Check the [issues](https://github.com/CrustaShrimp/Snake/issues).** You might be able to find the cause of the problem and fix things yourself. Most importantly, check if you can reproduce the problem in the latest version. If you do find the issue **and the issue is still open**, add a comment to the existing issue instead of opening a new one.
* **Determine whether it is really a bug.** Often it turns out bugs are actually feature request or just questions.

#### How Do I Submit A (Good) Bug Report?

Bugs are tracked as [issues](https://guides.github.com/features/issues/). After you've determined you have found a true bug, create an issue and provide the following information by filling in [the template](bug_report.md).

Explain the problem and include additional details to help maintainers reproduce the problem:

* **Use a clear and descriptive title** for the issue to identify the problem.
* **Describe the exact steps which reproduce the problem** in as many details as possible. For example, start by explaining how you started Snake, e.g. which build did you use etc. When listing steps, **don't just say what you did, but explain how you did it**. For example, if you pressed a menu item, explain if you used the mouse or the keyboard.
* **Provide specific examples to demonstrate the steps**. Include links to files or GitHub projects, or copy/pasteable snippets, which you use in those examples. If you're providing snippets in the issue, use [Markdown code blocks](https://help.github.com/articles/markdown-basics/#multiple-lines).
* **Describe the behavior you observed after following the steps** and point out what exactly is the problem with that behavior.
* **Explain which behavior you expected to see instead and why.**
* **Include screenshots and animated GIFs** which show you following the described steps and clearly demonstrate the problem. You can use [this tool](https://www.cockos.com/licecap/) to record GIFs on macOS and Windows, and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux.
* **If you're reporting that Snake crashed**, include a detailed crash report.
* **If the problem is related to performance or memory**, include a taskmanager screenshot as attachment.
* **If the problem wasn't triggered by a specific action**, describe what you were doing before the problem happened and share more information using the guidelines below.

Provide more context by answering these questions:

* **Did the problem start happening recently** (e.g. after updating to a new version of Snake) or was this always a problem?
* If the problem started happening recently, **can you reproduce the problem in an older version of Snake?** What's the most recent version in which the problem doesn't happen?
* **Can you reliably reproduce the issue?** If not, provide details about how often the problem happens and under which conditions it normally happens.
* If the problem is related to working with files (e.g. opening and editing files), **does the problem happen for all files and projects or only some?** Does the problem happen only when working with local or remote files (e.g. on network drives), with files of a specific type (e.g. only C++ files), with large files or files with very long lines, or with files in a specific encoding? Is there anything else special about the files you are using?

Include details about your configuration and environment:

* **Which version of Snake are you using?**
* **What's the name and version of the OS you're using**?
* **Which keyboard layout are you using?** Are you using a US layout or some other layout?

### Suggesting Features

This section guides you through submitting a feature suggestion for Snake, including completely new features and minor improvements to existing functionality. Following these guidelines helps maintainers and the community understand your suggestion and find related suggestions or ultimately implement your suggestion!

Before creating enhancement suggestions, please check [this list](#before-submitting-an-enhancement-suggestion) as you might find out that you don't need to create one. When you are creating an enhancement suggestion, please [include as many details as possible](#how-do-i-submit-a-good-enhancement-suggestion). Submit it [here](https://guides.github.com/features/issues/) using the template, including the steps that you imagine you would take if the feature you're requesting existed.

#### Before Submitting An Enhancement Suggestion

* **Check the [issues](https://guides.github.com/features/issues/)** for tips — you might discover that the enhancement is already available. Most importantly, check if you're using the latest version of Snake. If your feature has already been suggested, add a comment to the existing issue instead of opening a new one.
* **Determine the elements on which the feature has effect.**

#### How Do I Submit A (Good) Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](https://guides.github.com/features/issues/). After you've determined your enhancement suggestion is unique, create an issue and provide the following information:

* **Use a clear and descriptive title** for the issue to identify the suggestion.
* **Provide a step-by-step description of the suggested enhancement** in as many details as possible.
* **Provide specific examples to demonstrate the steps**. Include copy/pasteable snippets which you use in those examples, as [Markdown code blocks](https://help.github.com/articles/markdown-basics/#multiple-lines).
* **Describe the current behavior** and **explain which behavior you expected to see instead** and why.
* **Include screenshots and animated GIFs** which help you demonstrate the steps or point out the part of Snake which the suggestion is related to. You can use [this tool](https://www.cockos.com/licecap/) to record GIFs on macOS and Windows, and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux.
* **Explain why this enhancement would be useful** to most Snake users.
* **List some other applications where this enhancement exists.**
* **Specify which version of Snake you're using.**
* **Specify the name and version of the OS you're using.**

### Your First Code Contribution

Unsure where to begin contributing to Snake? You can start by looking through these `beginner` and `help-wanted` issues:

* [Good first issue](https://github.com/CrustaShrimp/Snake/labels/good%20first%20issue) - issues which should only require a few lines of code, and a test or two.
* [Help wanted issues](https://github.com/CrustaShrimp/Snake/labels/help%20wanted) - issues which should be a bit more involved than `beginner` issues.

Both issue lists are sorted by total number of comments. While not perfect, number of comments is a reasonable proxy for impact a given change will have.

### Pull Requests

The process described here has several goals:

- Maintain Snake's quality
- Fix problems that are important to users
- Engage the community in working toward the best possible Snake
- Enable a sustainable system for Snake's maintainers to review contributions

Please follow these steps to have your contribution considered by the maintainers:

1. Follow all instructions in [the template](PULL_REQUEST_TEMPLATE.md)
2. After you submit your pull request, verify that all [status checks](https://help.github.com/articles/about-status-checks/) are passing <details><summary>What if the status checks are failing?</summary>If a status check is failing, and you believe that the failure is unrelated to your change, please leave a comment on the pull request explaining why you believe the failure is unrelated. A maintainer will re-run the status check for you. If we conclude that the failure was a false positive, then we will open an issue to track that problem with our status check suite.</details>

While the prerequisites above must be satisfied prior to having your pull request reviewed, the reviewer(s) may ask you to complete additional design work, tests, or other changes before your pull request can be ultimately accepted.

## Styleguides

### Git Commit Messages

* Use the present tense ("Add feature" not "Added feature")
* Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
* Limit the first line to 72 characters or less
* Reference issues and pull requests liberally after the first line
* When only changing documentation, include `[Documentation]` in the commit title

## Additional Notes

### Issue and Pull Request Labels

This section lists the labels we use to help us track and manage issues and pull requests. 

[GitHub search](https://help.github.com/articles/searching-issues/) makes it easy to use labels for finding groups of issues or pull requests you're interested in. To help you find issues and pull requests, each label is listed with search links for finding open items with that label. We  encourage you to read about [other search filters](https://help.github.com/articles/searching-issues/) which will help you write more focused queries.

The labels are loosely grouped by their purpose, but it's not required that every issue have a label from every group or that an issue can't have more than one label from the same group.

Please open an issue if you have suggestions for new labels if you notice some labels are missing.

#### Type of Issue and Issue State

| Label name | Description |
| --- | --- |
| `Approved FR` | Approved feature requests, to be implemented. |
| `bug`| Unconfirmed bugs. |
| `documentation` | Focussed mainly on documentation in code or on GitHub. |
| `duplicate` | Issue already filed earlier. |
| `enhancement` | Feature requests, not yet verified. Should be examined first before being implem |
| `good first issue` | Less complex issues which would be good first issues to work on for users who want to contribute to Snake. |
| `help-wanted` | The Snake core team would appreciate help from the community in resolving these issues. |
| `invalid` | Issues which aren't valid (e.g. user errors). |
| `question` | Questions more than bug reports or feature requests (e.g. how do I do X). |
| `Triage requested` | Issue needs to be checked by the team before it is approved. |
| `bug` | Confirmed bugs or reports that are very likely to be bugs. |
| `wontfix` | The Snake core team has decided not to fix these issues for now, either because they're working as intended or for some other reason. |
