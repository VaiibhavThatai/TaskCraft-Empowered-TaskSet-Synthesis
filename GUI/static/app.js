$(document).ready(function () {
    $("form").submit(function (event) {
      event.preventDefault();
      $.post("/generate_task_sets", $(this).serialize(), function (response) {
        var outputDiv = $("#output");
        outputDiv.empty();
        // Display the generated task sets
        response.taskSets.forEach(function (taskSet) {
          outputDiv.append(taskSet.join(" ") + "\n");
        });
      }).fail(function (xhr) {
        $("#output").text(xhr.responseText);
      });
    });
  });
  