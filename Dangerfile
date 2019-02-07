# Make it more obvious that a PR is a work in progress and shouldn't be merged yet
warn "PR is classed as Work in Progress" if github.pr_title.include? "[WIP]"

# Warn when there is a big PR
warn "Big PR based on #{git.lines_of_code} LOC" if git.lines_of_code > 1000

# Fail if the PR body is too short
fail "Please provide a more verbose summary in the PR description" if github.pr_body.length < 30

# Refactoring old code is great
message ":thumbsup: You deleted more code than you added!" if github.pr_json.deletions > github.pr_json.additions

# First time contributor, yeah!
message ":confetti_ball: Awesome, your first PR! Good job" if github.pr_json.author_association == "FIRST_TIME_CONTRIBUTOR"

markdown File.read(File.expand_path "~/lintout.md") if File.exist?(File.expand_path "~/lintout.md")
fail "Linter Failed to execute" if not File.exist?(File.expand_path "~/lintout.md") and File.exist?(File.expand_path "~/lintout_errors.md") 

markdown File.read(File.expand_path "~/lintout_errors.md") if File.exist?(File.expand_path "~/lintout_errors.md")
fail "Linter Failed" if File.exist?(File.expand_path "~/lintout_errors.md")

# Add some labels to help in PR review and finding PRs
labels = Array.new
labels << "WIP" if github.pr_title.include? "[WIP]"
labels << "physics" if git.added_files.include?("physics") or git.modified_files.include?("physics")
labels << "linter" if git.added_files.include?("lint") or git.modified_files.include?("lint")
github.api.add_labels_to_an_issue("tmcgillicuddy/nilsmath", github.pr_json.number, labels) if not labels.empty?