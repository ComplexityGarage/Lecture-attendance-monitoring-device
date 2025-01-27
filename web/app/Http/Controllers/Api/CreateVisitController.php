<?php

namespace App\Http\Controllers\Api;

use App\Events\VisitCreated;
use App\Http\Controllers\Controller;
use App\Models\Visit;
use Illuminate\Http\Request;

class CreateVisitController extends Controller
{
    public function __invoke(Request $request)
    {
        $visit = Visit::create($request->only('hash'));

        VisitCreated::dispatch($visit);

        return response()->json(['success' => true]);
    }
}
